DROP TABLE "ROOT"."movie";
CREATE TABLE "ROOT"."movie"(
	movieId BIGINT NOT NULL PRIMARY KEY GENERATED ALWAYS AS IDENTITY (START WITH 1, INCREMENT BY 1), 
	title VARCHAR(80) NOT NULL, 
	director VARCHAR(80) NOT NULL
);