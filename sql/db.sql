DROP TABLE IF EXISTS sms;
DROP TABLE IF EXISTS mobile_provider;
DROP TABLE IF EXISTS pill_description;
DROP TABLE IF EXISTS reminder;
DROP TABLE IF EXISTS users;

-- User table
CREATE TABLE users(
    ID SERIAL PRIMARY KEY NOT NULL,
    EMAIL VARCHAR(255) UNIQUE NOT NULL,
    PASSWORD_H TEXT NOT NULL,
    FIRST_NAME VARCHAR(255) NOT NULL,
    LAST_NAME VARCHAR(255) NOT NULL,
    IS_ENGLISH BOOLEAN NOT NULL
);

-- Reminder table
CREATE TABLE reminder(
    ID SERIAL PRIMARY KEY NOT NULL,
    USER_ID INT NOT NULL REFERENCES users(ID),
    DAY TEXT NOT NULL,
    DAY_TIME TIMESTAMP NOT NULL
);

-- Pill table
CREATE TABLE pill_description(
    ID SERIAL PRIMARY KEY NOT NULL,
    REMINDER_ID INT REFERENCES reminder(ID),
    PILL_NAME TEXT NOT NULL,
    AMOUNT SMALLINT NOT NULL,
    STRENGTH SMALLINT,
    REMAINING SMALLINT
);

-- Mobile provider table
CREATE TABLE mobile_provider(
    ID SERIAL PRIMARY KEY NOT NULL,
    PROVIDER_URI VARCHAR(32) NOT NULL UNIQUE
);

-- SMS table
CREATE TABLE sms(
    ID SERIAL PRIMARY KEY NOT NULL,
    USERS_ID INT REFERENCES users(ID),
    PILL_DESCRIPTION_ID INT REFERENCES pill_description(ID),
    PHONE_NUMBER SMALLINT NOT NULL,
    PHONE_PROVIDER SMALLINT REFERENCES mobile_provider(ID)
);

