SELECT movies.title,
       ratings.rating
FROM   movies
       LEFT JOIN ratings
              ON ratings.movie_id = movies.id
WHERE  movies.year = 2010
       AND ratings.rating IS NOT NULL
ORDER BY ratings.rating DESC, title;