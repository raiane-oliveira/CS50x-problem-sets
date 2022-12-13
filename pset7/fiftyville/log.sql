-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Seleciona a descrição do dia em que ocorreu o roubo
SELECT description
  FROM crime_scene_reports
 WHERE day = 28
   AND month = 7
   AND street = "Humphrey Street";

-- leitura das transcrições das testemunhas no dia
SELECT transcript
  FROM interviews
 WHERE day = 28
   AND month = 7;

-- Lista de carros que saíram do estacionamente da padaria
SELECT *
  FROM bakery_security_logs
 WHERE day = 28
   AND month = 7
   AND hour = 10
   AND activity = "exit";
+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
| 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
| 268 | 2021 | 7     | 28  | 10   | 35     | exit     | 1106N58       |
+-----+------+-------+-----+------+--------+----------+---------------+
-- Lista das pessoas com as placas do carros compatíveis
SELECT *
  FROM people
 WHERE license_plate IN
       (SELECT license_plate
          FROM bakery_security_logs
         WHERE day = 28
           AND month = 7
           AND hour = 10
           AND activity = "exit");
+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
| 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+---------+----------------+-----------------+---------------+
-- Ligações que ocorreram no dia do roubo com menos de 1 min
SELECT *
  FROM phone_calls
 WHERE day = 28
   AND month = 7
   AND duration < 60;
+----------------+----------------+
|     caller     |    receiver    |
+----------------+----------------+
| (130) 555-0289 | (996) 555-8899 |
| (499) 555-9472 | (892) 555-8872 |
| (367) 555-5533 | (375) 555-8161 |
| (499) 555-9472 | (717) 555-1342 |
| (286) 555-6063 | (676) 555-6554 |
| (770) 555-1861 | (725) 555-3243 |
+----------------+----------------+
-- Aeroporto de Fiftyville
SELECT *
  FROM airports
 WHERE city = "Fiftyville";
+----+--------------+-----------------------------+------------+
| id | abbreviation |          full_name          |    city    |
+----+--------------+-----------------------------+------------+
| 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
+----+--------------+-----------------------------+------------+

-- Voos de Fiftyville do dia seguinte ao roubo
SELECT *
  FROM flights
 WHERE origin_airport_id = 8
   AND day = 29
   AND month = 7;
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
+----+-------------------+------------------------+------+-------+-----+------+--------+

-- Mostra para qual cidade o ladrão fugiu
SELECT *
  FROM airports
 WHERE id = 4;
 +----+--------------+-------------------+---------------+
| id | abbreviation |     full_name     |     city      |
+----+--------------+-------------------+---------------+
| 4  | LGA          | LaGuardia Airport | New York City |
+----+--------------+-------------------+---------------+

-- Verifica se a lista de suspeitos voou nesse voo
SELECT *
  FROM passengers
 WHERE flight_id = 36
   AND passport_number IN ("5773159633", "1988161715");

-- Lista dos cúmplices
SELECT *
  FROM people
 WHERE phone_number IN ("(996) 555-8899", "(367) 555-5533");
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       |
+--------+-------+----------------+-----------------+---------------+
-- As contas bancárias dos suspeitos
SELECT *
  FROM bank_accounts
 WHERE person_id IN (398010, 686048);
+----------------+-----------+---------------+
| account_number | person_id | creation_year |
+----------------+-----------+---------------+
| 49610011       | 686048    | 2010          |
+----------------+-----------+---------------+

-- Verifica se essa conta sacou no dia do roubo, na Leggett Street
SELECT *
  FROM atm_transactions
 WHERE day = 28
   AND month = 7
   AND account_number = 49610011
   AND transaction_type = "withdraw";
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+