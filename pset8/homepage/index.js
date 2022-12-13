document.querySelector('.btn-dark').addEventListener('click', function() {
    var img = document.createElement("IMG");
    img.src = "https://cdn.cs50.net/2021/fall/lectures/8/src8/cat.gif";
    img.style.height = "100px";
    document.getElementById("hidden").append(img);
});