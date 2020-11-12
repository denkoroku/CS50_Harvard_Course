SELECT DISTINCT name FROM people
INNER JOIN directors ON people.id = directors.person_id
INNER JOIN ratings ON ratings.movie_id = directors.movie_id
WHERE ratings.rating >= 9