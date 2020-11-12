SELECT title FROM movies
INNER JOIN stars ON movies.id = stars.movie_id
INNER JOIN people ON people.id = stars.person_id
INNER JOIN ratings ON ratings.movie_id = stars.movie_id
WHERE people.name = "Chadwick Boseman"
ORDER BY ratings.rating
LIMIT 5
