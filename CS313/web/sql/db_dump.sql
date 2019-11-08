--
-- PostgreSQL database dump
--

-- Dumped from database version 10.3 (Ubuntu 10.3-1.pgdg16.04+1)
-- Dumped by pg_dump version 10.4 (Ubuntu 10.4-1.pgdg16.04+1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: image_comments; Type: TABLE; Schema: public; Owner: apixsmlubzrrza
--

CREATE TABLE public.image_comments (
    id integer NOT NULL,
    comment text,
    image_commented integer,
    user_commented integer,
    CONSTRAINT image_comments_comment_check CHECK ((char_length(comment) <= 200))
);


ALTER TABLE public.image_comments OWNER TO apixsmlubzrrza;

--
-- Name: image_comments_id_seq; Type: SEQUENCE; Schema: public; Owner: apixsmlubzrrza
--

CREATE SEQUENCE public.image_comments_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.image_comments_id_seq OWNER TO apixsmlubzrrza;

--
-- Name: image_comments_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: apixsmlubzrrza
--

ALTER SEQUENCE public.image_comments_id_seq OWNED BY public.image_comments.id;


--
-- Name: images; Type: TABLE; Schema: public; Owner: apixsmlubzrrza
--

CREATE TABLE public.images (
    id integer NOT NULL,
    title text NOT NULL,
    description text,
    image_view_count integer NOT NULL,
    image_likes integer NOT NULL,
    date_posted timestamp without time zone NOT NULL,
    user_uploaded_id integer,
    CONSTRAINT images_title_check CHECK ((char_length(title) <= 70))
);


ALTER TABLE public.images OWNER TO apixsmlubzrrza;

--
-- Name: images_id_seq; Type: SEQUENCE; Schema: public; Owner: apixsmlubzrrza
--

CREATE SEQUENCE public.images_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.images_id_seq OWNER TO apixsmlubzrrza;

--
-- Name: images_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: apixsmlubzrrza
--

ALTER SEQUENCE public.images_id_seq OWNED BY public.images.id;


--
-- Name: users; Type: TABLE; Schema: public; Owner: apixsmlubzrrza
--

CREATE TABLE public.users (
    id integer NOT NULL,
    email text NOT NULL,
    password_s text NOT NULL,
    first_name text NOT NULL,
    last_name text NOT NULL,
    popularity integer NOT NULL,
    date_joined timestamp without time zone NOT NULL,
    CONSTRAINT users_email_check CHECK ((char_length(email) <= 255))
);


ALTER TABLE public.users OWNER TO apixsmlubzrrza;

--
-- Name: users_id_seq; Type: SEQUENCE; Schema: public; Owner: apixsmlubzrrza
--

CREATE SEQUENCE public.users_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.users_id_seq OWNER TO apixsmlubzrrza;

--
-- Name: users_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: apixsmlubzrrza
--

ALTER SEQUENCE public.users_id_seq OWNED BY public.users.id;


--
-- Name: video_comments; Type: TABLE; Schema: public; Owner: apixsmlubzrrza
--

CREATE TABLE public.video_comments (
    id integer NOT NULL,
    comment text,
    video_commented integer,
    user_commented integer,
    CONSTRAINT video_comments_comment_check CHECK ((char_length(comment) <= 200))
);


ALTER TABLE public.video_comments OWNER TO apixsmlubzrrza;

--
-- Name: video_comments_id_seq; Type: SEQUENCE; Schema: public; Owner: apixsmlubzrrza
--

CREATE SEQUENCE public.video_comments_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.video_comments_id_seq OWNER TO apixsmlubzrrza;

--
-- Name: video_comments_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: apixsmlubzrrza
--

ALTER SEQUENCE public.video_comments_id_seq OWNED BY public.video_comments.id;


--
-- Name: videos; Type: TABLE; Schema: public; Owner: apixsmlubzrrza
--

CREATE TABLE public.videos (
    id integer NOT NULL,
    title text NOT NULL,
    description text,
    video_view_count integer NOT NULL,
    video_likes integer NOT NULL,
    date_posted timestamp without time zone NOT NULL,
    user_uploaded_id integer,
    CONSTRAINT videos_description_check CHECK ((char_length(description) <= 100)),
    CONSTRAINT videos_title_check CHECK ((char_length(title) <= 70))
);


ALTER TABLE public.videos OWNER TO apixsmlubzrrza;

--
-- Name: videos_id_seq; Type: SEQUENCE; Schema: public; Owner: apixsmlubzrrza
--

CREATE SEQUENCE public.videos_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.videos_id_seq OWNER TO apixsmlubzrrza;

--
-- Name: videos_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: apixsmlubzrrza
--

ALTER SEQUENCE public.videos_id_seq OWNED BY public.videos.id;


--
-- Name: image_comments id; Type: DEFAULT; Schema: public; Owner: apixsmlubzrrza
--

ALTER TABLE ONLY public.image_comments ALTER COLUMN id SET DEFAULT nextval('public.image_comments_id_seq'::regclass);


--
-- Name: images id; Type: DEFAULT; Schema: public; Owner: apixsmlubzrrza
--

ALTER TABLE ONLY public.images ALTER COLUMN id SET DEFAULT nextval('public.images_id_seq'::regclass);


--
-- Name: users id; Type: DEFAULT; Schema: public; Owner: apixsmlubzrrza
--

ALTER TABLE ONLY public.users ALTER COLUMN id SET DEFAULT nextval('public.users_id_seq'::regclass);


--
-- Name: video_comments id; Type: DEFAULT; Schema: public; Owner: apixsmlubzrrza
--

ALTER TABLE ONLY public.video_comments ALTER COLUMN id SET DEFAULT nextval('public.video_comments_id_seq'::regclass);


--
-- Name: videos id; Type: DEFAULT; Schema: public; Owner: apixsmlubzrrza
--

ALTER TABLE ONLY public.videos ALTER COLUMN id SET DEFAULT nextval('public.videos_id_seq'::regclass);


--
-- Data for Name: image_comments; Type: TABLE DATA; Schema: public; Owner: apixsmlubzrrza
--

COPY public.image_comments (id, comment, image_commented, user_commented) FROM stdin;
\.


--
-- Data for Name: images; Type: TABLE DATA; Schema: public; Owner: apixsmlubzrrza
--

COPY public.images (id, title, description, image_view_count, image_likes, date_posted, user_uploaded_id) FROM stdin;
\.


--
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: apixsmlubzrrza
--

COPY public.users (id, email, password_s, first_name, last_name, popularity, date_joined) FROM stdin;
1	lol@lol.com	haha	DAVE	PER	0	2018-05-19 00:00:00
\.


--
-- Data for Name: video_comments; Type: TABLE DATA; Schema: public; Owner: apixsmlubzrrza
--

COPY public.video_comments (id, comment, video_commented, user_commented) FROM stdin;
\.


--
-- Data for Name: videos; Type: TABLE DATA; Schema: public; Owner: apixsmlubzrrza
--

COPY public.videos (id, title, description, video_view_count, video_likes, date_posted, user_uploaded_id) FROM stdin;
1	Look at this...	at home	0	4	2018-05-19 00:00:00	1
\.


--
-- Name: image_comments_id_seq; Type: SEQUENCE SET; Schema: public; Owner: apixsmlubzrrza
--

SELECT pg_catalog.setval('public.image_comments_id_seq', 1, false);


--
-- Name: images_id_seq; Type: SEQUENCE SET; Schema: public; Owner: apixsmlubzrrza
--

SELECT pg_catalog.setval('public.images_id_seq', 1, false);


--
-- Name: users_id_seq; Type: SEQUENCE SET; Schema: public; Owner: apixsmlubzrrza
--

SELECT pg_catalog.setval('public.users_id_seq', 1, true);


--
-- Name: video_comments_id_seq; Type: SEQUENCE SET; Schema: public; Owner: apixsmlubzrrza
--

SELECT pg_catalog.setval('public.video_comments_id_seq', 1, false);


--
-- Name: videos_id_seq; Type: SEQUENCE SET; Schema: public; Owner: apixsmlubzrrza
--

SELECT pg_catalog.setval('public.videos_id_seq', 1, true);


--
-- Name: image_comments image_comments_pkey; Type: CONSTRAINT; Schema: public; Owner: apixsmlubzrrza
--

ALTER TABLE ONLY public.image_comments
    ADD CONSTRAINT image_comments_pkey PRIMARY KEY (id);


--
-- Name: images images_pkey; Type: CONSTRAINT; Schema: public; Owner: apixsmlubzrrza
--

ALTER TABLE ONLY public.images
    ADD CONSTRAINT images_pkey PRIMARY KEY (id);


--
-- Name: users users_pkey; Type: CONSTRAINT; Schema: public; Owner: apixsmlubzrrza
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_pkey PRIMARY KEY (id);


--
-- Name: video_comments video_comments_pkey; Type: CONSTRAINT; Schema: public; Owner: apixsmlubzrrza
--

ALTER TABLE ONLY public.video_comments
    ADD CONSTRAINT video_comments_pkey PRIMARY KEY (id);


--
-- Name: videos videos_pkey; Type: CONSTRAINT; Schema: public; Owner: apixsmlubzrrza
--

ALTER TABLE ONLY public.videos
    ADD CONSTRAINT videos_pkey PRIMARY KEY (id);


--
-- Name: image_comments image_comments_image_commented_fkey; Type: FK CONSTRAINT; Schema: public; Owner: apixsmlubzrrza
--

ALTER TABLE ONLY public.image_comments
    ADD CONSTRAINT image_comments_image_commented_fkey FOREIGN KEY (image_commented) REFERENCES public.images(id);


--
-- Name: image_comments image_comments_user_commented_fkey; Type: FK CONSTRAINT; Schema: public; Owner: apixsmlubzrrza
--

ALTER TABLE ONLY public.image_comments
    ADD CONSTRAINT image_comments_user_commented_fkey FOREIGN KEY (user_commented) REFERENCES public.users(id);


--
-- Name: images images_user_uploaded_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: apixsmlubzrrza
--

ALTER TABLE ONLY public.images
    ADD CONSTRAINT images_user_uploaded_id_fkey FOREIGN KEY (user_uploaded_id) REFERENCES public.users(id);


--
-- Name: video_comments video_comments_user_commented_fkey; Type: FK CONSTRAINT; Schema: public; Owner: apixsmlubzrrza
--

ALTER TABLE ONLY public.video_comments
    ADD CONSTRAINT video_comments_user_commented_fkey FOREIGN KEY (user_commented) REFERENCES public.users(id);


--
-- Name: video_comments video_comments_video_commented_fkey; Type: FK CONSTRAINT; Schema: public; Owner: apixsmlubzrrza
--

ALTER TABLE ONLY public.video_comments
    ADD CONSTRAINT video_comments_video_commented_fkey FOREIGN KEY (video_commented) REFERENCES public.videos(id);


--
-- Name: videos videos_user_uploaded_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: apixsmlubzrrza
--

ALTER TABLE ONLY public.videos
    ADD CONSTRAINT videos_user_uploaded_id_fkey FOREIGN KEY (user_uploaded_id) REFERENCES public.users(id);


--
-- Name: SCHEMA public; Type: ACL; Schema: -; Owner: apixsmlubzrrza
--

REVOKE ALL ON SCHEMA public FROM postgres;
REVOKE ALL ON SCHEMA public FROM PUBLIC;
GRANT ALL ON SCHEMA public TO apixsmlubzrrza;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- Name: LANGUAGE plpgsql; Type: ACL; Schema: -; Owner: postgres
--

GRANT ALL ON LANGUAGE plpgsql TO apixsmlubzrrza;


--
-- PostgreSQL database dump complete
--

