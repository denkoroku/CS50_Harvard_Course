SELECT DISTINCT name FROM people
INNER JOIN movies ON movies.id = stars.movie_id
INNER JOIN stars ON people.id = stars.person_id
WHERE  movies.id IN (

SELECT movies.id FROM people
INNER JOIN stars ON movies.id = stars.movie_id
INNER JOIN movies ON people.id = stars.person_id
WHERE people.name = "Kevin Bacon" AND people.birth = 1958 )

AND people.name != "Kevin Bacon"