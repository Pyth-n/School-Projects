
-- PATH: /home/pi/lol/web/lol.sql

-- Drops table if it exists
DROP TABLE IF EXISTS image_comments;
DROP TABLE IF EXISTS images;
DROP TABLE IF EXISTS video_comments;
DROP TABLE IF EXISTS videos;
DROP TABLE IF EXISTS users;

-- Create the table FIRST to test it out
CREATE TABLE users(
	ID SERIAL PRIMARY KEY NOT NULL,
	EMAIL TEXT CHECK(char_length(EMAIL) <= 255) UNIQUE NOT NULL,
	PASSWORD_S TEXT NOT NULL,
	FIRST_NAME TEXT NOT NULL,
	LAST_NAME TEXT NOT NULL,
	POPULARITY INT DEFAULT 0,
	DATE_JOINED TIMESTAMP NOT NULL
);

CREATE TABLE videos(
	ID SERIAL PRIMARY KEY NOT NULL,
	TITLE TEXT CHECK(char_length(TITLE) <= 70) NOT NULL,
	DESCRIPTION TEXT CHECK(char_length(DESCRIPTION) <= 100),
	VIDEO_VIEW_COUNT INT DEFAULT 0,
	VIDEO_LIKES INT DEFAULT 0,
	DATE_POSTED TIMESTAMP NOT NULL,
	USER_UPLOADED_ID INT REFERENCES users(ID)
);

CREATE TABLE images(
	ID SERIAL PRIMARY KEY NOT NULL,
	TITLE TEXT CHECK(char_length(TITLE) <= 70) NOT NULL,
	DESCRIPTION TEXT,
	IMAGE_VIEW_COUNT INT DEFAULT 0,
	IMAGE_LIKES INT DEFAULT 0,
	DATE_POSTED TIMESTAMP NOT NULL,
	USER_UPLOADED_ID INT REFERENCES users(ID)
);

CREATE TABLE video_comments(
	ID SERIAL PRIMARY KEY NOT NULL,
	COMMENT TEXT CHECK(char_length(COMMENT) <= 200),
	VIDEO_COMMENTED INT REFERENCES videos(ID),
	USER_COMMENTED INT REFERENCES users(ID)
);



CREATE TABLE image_comments(
	ID SERIAL PRIMARY KEY NOT NULL,
	COMMENT TEXT CHECK(char_length(COMMENT) <= 200),
	IMAGE_COMMENTED INT REFERENCES images(ID),
	USER_COMMENTED INT REFERENCES users(ID)
);

-- Use this script to populate
INSERT INTO users (EMAIL, PASSWORD_S, FIRST_NAME, LAST_NAME, POPULARITY, DATE_JOINED)
VALUES (
	'lol@lol.com',
	'haha',
	'DAVE',
	'PER',
	0,
	current_timestamp
);

INSERT INTO users (EMAIL, PASSWORD_S, FIRST_NAME, LAST_NAME, POPULARITY, DATE_JOINED)
VALUES (
	'bob@lol.com',
	'bob123',
	'bob',
	'builder',
	2,
	current_timestamp
);

INSERT INTO users (EMAIL, PASSWORD_S, FIRST_NAME, LAST_NAME, POPULARITY, DATE_JOINED)
VALUES (
	'john@lol.com',
	'john312',
	'john',
	'smith',
	0,
	current_timestamp
);

INSERT INTO users (EMAIL, PASSWORD_S, FIRST_NAME, LAST_NAME, POPULARITY, DATE_JOINED)
VALUES (
	'jose@lol.com',
	'password1',
	'jose',
	'corre',
	0,
	current_timestamp
);

INSERT INTO users (EMAIL, PASSWORD_S, FIRST_NAME, LAST_NAME, POPULARITY, DATE_JOINED)
VALUES (
	'jane@lol.com',
	'doejane',
	'Jane',
	'Doe',
	0,
	current_timestamp
);

INSERT INTO users (EMAIL, PASSWORD_S, FIRST_NAME, LAST_NAME, POPULARITY, DATE_JOINED)
VALUES (
	'bobsmith@lol.com',
	'smithybobby',
	'Bob',
	'Smith',
	0,
	current_timestamp
);
/*INSERT INTO videos( TITLE
	, DESCRIPTION
	, VIDEO_VIEW_COUNT
	, VIDEO_LIKES
	, DATE_POSTED
	, USER_UPLOADED_ID
)
VALUES (
	'Look at this...',
	'at home',
	0,
	4,
	current_date,
	1
);*/
