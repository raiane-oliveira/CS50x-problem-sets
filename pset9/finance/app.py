import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# Remember the current user
USER = 0


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Remember user
    USER = session["user_id"]

    # Gets cash of the user
    cash = db.execute("SELECT cash FROM users WHERE ID = ?", USER)

    # Checks if have an purchase
    purchase = db.execute("SELECT * FROM purchase WHERE person_id = ?", USER)
    if not purchase:
        return render_template("index.html", cash=cash[0]["cash"])

    # Sets the total holding of each stock
    for data in purchase:
        holding = data["shares"] * data["price"]
        db.execute("UPDATE purchase SET total = ? WHERE symbol = ? AND person_id = ?", holding, data["symbol"], USER)

    # Sum the total values
    total = db.execute("SELECT SUM(total) AS total FROM purchase WHERE person_id = ?", USER)
    total = total[0]["total"] + cash[0]["cash"]

    # Select purchase again
    purchase = db.execute("SELECT * FROM purchase WHERE person_id = ?", USER)

    return render_template("index.html", purchase=purchase, cash=cash[0]["cash"], total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # Remember user
    USER = session["user_id"]

    # Via POST
    if request.method == "POST":

        # Gets symbol and shares
        stock = lookup(request.form.get("symbol"))
        shares = request.form.get("shares")

        # Cheking erros
        if not request.form.get("symbol") or not shares:
            return apology("missing symbol and/or shares!")
        if stock is None:
            return apology("invalid symbol!")
        if not shares.isdigit():
            return apology("invalid shares!")
        if shares.isdigit() and int(shares) < 0:
            return apology("negative shares!")

        shares = int(shares)

        # Gets user money
        cash = db.execute("SELECT cash FROM users WHERE id = ?", USER)
        cash = cash[0]["cash"]

        # Checks if the user has enough money
        owe = stock["price"] * shares
        if cash < owe:
            return apology("You don't have enough money!")

        # Keeps track of purchase
        purchase = db.execute("SELECT * FROM purchase WHERE symbol = ? AND person_id = ?", stock["symbol"], USER)

        # Sets the transaction time
        time_purchase = datetime.datetime.now()
        db.execute("INSERT INTO transactions (transacted, symbol_purchase, price_purchase, shares_purchase, person_id) VALUES (?, ?, ?, ?, ?)",
                   time_purchase, stock["symbol"], stock["price"], shares, USER)

        # Adds purchase or update it
        if not purchase or purchase[0]["symbol"] != stock["symbol"]:
            db.execute("INSERT INTO purchase (symbol, name, shares, price, person_id) VALUES (?, ?, ?, ?, ?)",
                       stock["symbol"], stock["name"], shares, stock["price"], USER)
        else:
            sum_shares = db.execute("SELECT shares FROM purchase WHERE person_id = ? AND symbol = ?", USER, stock["symbol"])
            shares += sum_shares[0]["shares"]
            db.execute("UPDATE purchase SET shares = ? WHERE person_id = ? AND symbol = ?", shares, USER, stock["symbol"])

        # Update the current cash of the user
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - owe, USER)

        return redirect("/")

    # Via GET
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Remember user
    USER = session["user_id"]

    # Gets all transactions made
    transactions = db.execute("SELECT * FROM transactions WHERE person_id = ?", USER)

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # Via POST
    if request.method == "POST":

        # Gets name, price and symbol of stock
        stock = lookup(request.form.get("symbol"))

        # Cheking erros
        if not request.form.get("symbol"):
            return apology("missing symbol!")
        if stock is None:
            return apology("invalid symbol!")

        # Renders the data of a stock
        return render_template("quoted.html", stock=stock)

    # Via GET
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Gets data
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Access duplicates
        duplicate_user = db.execute("SELECT username FROM users WHERE username = ?", username)

        # Checking erros
        if not username or not password or not confirmation:
            return apology("must provide username, password and/or confirmation!")
        if confirmation != password:
            return apology("Passwords must be the same!")
        if duplicate_user:
            return apology("This username is already in use")

        # Change the plaintext password to hash code
        security_password = generate_password_hash(password)

        # Adding to the database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, security_password)

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Remember user
    USER = session["user_id"]

    # Symbols of stock that user owns
    symbols = db.execute("SELECT symbol FROM purchase WHERE person_id = ?", USER)

    # Via POST
    if request.method == "POST":

        # Gets inputs data
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Gets user purchase
        purchase = db.execute("SELECT * FROM purchase WHERE person_id = ? AND symbol = ?", USER, symbol)

        # Checking erros
        if not symbol or not shares:
            return apology("missing symbol and/or shares!")
        if not shares.isdigit():
            return apology("invalid shares!")
        if shares.isdigit():
            shares = int(shares)
            if shares < 0 or shares > purchase[0]["shares"]:
                return apology("too much shares or negative shares!")

        # Gets the user money, the total sold and the shares sold
        total_sold = purchase[0]["price"] * shares
        cash = db.execute("SELECT cash FROM users WHERE id = ?", USER)
        sold_shares = shares * (-1)

        # Sets transaction time
        time_purchase = datetime.datetime.now()
        db.execute("INSERT INTO transactions (transacted, symbol_purchase, price_purchase, shares_purchase, person_id) VALUES (?, ?, ?, ?, ?)",
                   time_purchase, symbol, purchase[0]["price"], sold_shares, USER)

        # Sell the stock
        if purchase[0]["shares"] == shares:
            db.execute("DELETE FROM purchase WHERE shares = ? AND symbol = ? AND person_id = ?", shares, symbol, USER)
            db.execute("UPDATE users SET cash = ? WHERE id = ?", total_sold + cash[0]["cash"], USER)
        else:
            db.execute("UPDATE purchase SET shares = ? WHERE symbol = ? AND person_id = ?",
                       purchase[0]["shares"] - shares, symbol, USER)
            db.execute("UPDATE users SET cash = ? WHERE id = ?", total_sold + cash[0]["cash"], USER)

        return redirect("/")

    # Via GET
    else:
        return render_template("sell.html", symbols=symbols)


@app.route("/cash", methods=["POST", "GET"])
@login_required
def cash():
    """Add money to user account"""

    # Remember user
    USER = session["user_id"]

    # Via POST
    if request.method == "POST":

        # Gets the amount of money that the user wants to add
        amount_money = request.form.get("money")

        # Gets the current cash of user
        cash = db.execute("SELECT cash FROM users WHERE id = ?", USER)

        # Checking erros
        if not amount_money:
            return apology("the input is empty!")
        if not amount_money.isdigit() or int(amount_money) < 0:
            return apology("invalid digits!")

        # Add the money to account
        db.execute("UPDATE users SET cash = ?", int(amount_money) + cash[0]["cash"])

        return redirect("/")

    # Via GET
    else:
        return render_template("cash.html")


@app.route("/password", methods=["POST", "GET"])
@login_required
def password():
    """Change the password of the user"""

    # Remember user
    USER = session["user_id"]

    # via POST
    if request.method == "POST":

        # Gets data from form
        old_pass = request.form.get("old_pass")
        new_pass = request.form.get("new_pass")
        confirmation = request.form.get("confirmation")

        # Gets the hashed password to verify the user
        hash_user = db.execute("SELECT hash FROM users WHERE id = ?", USER)

        # Checking erros
        if not old_pass or not new_pass or not confirmation:
            return apology("missing fields!")
        if not check_password_hash(hash_user[0]["hash"], old_pass):
            return apology("incorrect password!")
        if new_pass != confirmation:
            return apology("passwords must be the same!")
        if check_password_hash(hash_user[0]["hash"], new_pass):
            return apology("you can't update to the same password!")

        # Hash new password
        security_password = generate_password_hash(new_pass)

        # Update the password
        db.execute("UPDATE users SET hash = ? WHERE id = ?", security_password, USER)

        # Redirect to login
        return redirect("/login")

    # via GET
    else:
        return render_template("password.html")