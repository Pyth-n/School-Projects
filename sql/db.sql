DROP TABLE IF EXISTS sms CASCADE;
DROP TABLE IF EXISTS mobile_provider CASCADE;
DROP TABLE IF EXISTS reminder CASCADE ;
DROP TABLE IF EXISTS pill_description CASCADE;
DROP TABLE IF EXISTS users CASCADE;

-- Mobile provider table
CREATE TABLE mobile_provider(
    ID SERIAL PRIMARY KEY NOT NULL,
    PROVIDER_URI VARCHAR(32) NOT NULL UNIQUE
);

-- User table
CREATE TABLE users(
    ID SERIAL PRIMARY KEY NOT NULL,
    EMAIL VARCHAR(255) UNIQUE NOT NULL,
    PASSWORD_H TEXT NOT NULL,
    FIRST_NAME VARCHAR(255) NOT NULL,
    LAST_NAME VARCHAR(255) NOT NULL,
    IS_ENGLISH BOOLEAN NOT NULL,
    TOKEN TEXT,
    PHONE_NUMBER INT NOT NULL,
    PHONE_PROVIDER SMALLINT NOT NULL REFERENCES mobile_provider(ID)
);

-- Pill table
CREATE TABLE pill_description(
    ID SERIAL PRIMARY KEY NOT NULL,
    USER_ID INT NOT NULL REFERENCES users(ID),
    PILL_NAME TEXT NOT NULL,
    AMOUNT SMALLINT NOT NULL,
    STRENGTH TEXT,
    REMAINING SMALLINT
);

-- Reminder table
CREATE TABLE reminder(
    ID SERIAL PRIMARY KEY NOT NULL,
    PILL_ID INT NOT NULL REFERENCES pill_description(ID),
    HOUR SMALLINT NOT NULL,
    MINUTE SMALLINT NOT NULL
);

-- SMS table
CREATE TABLE sms(
    ID SERIAL PRIMARY KEY NOT NULL,
    USERS_ID INT REFERENCES users(ID),
    PILL_DESCRIPTION_ID INT REFERENCES pill_description(ID)
);

-- Populate movile_provider
INSERT INTO mobile_provider(PROVIDER_URI)
VALUES (
    '@message.alltel.com'
);

INSERT INTO mobile_provider(PROVIDER_URI)
VALUES (
    '@txt.att.net'
);

INSERT INTO mobile_provider(PROVIDER_URI)
VALUES (
    '@myboostmobile.com'
);

INSERT INTO mobile_provider(PROVIDER_URI)
VALUES (
    '@messaging.sprintpcs.com'
);

INSERT INTO mobile_provider(PROVIDER_URI)
VALUES (
    '@tmomail.net'
);

INSERT INTO mobile_provider(PROVIDER_URI)
VALUES (
    '@email.uscc.net'
);

INSERT INTO mobile_provider(PROVIDER_URI)
VALUES (
    '@vtext.com'
);

INSERT INTO mobile_provider(PROVIDER_URI)
VALUES (
    '@vmobl.com'
);

INSERT INTO mobile_provider(PROVIDER_URI)
VALUES (
    '@text.republicwireless.com'
);