-- DROP DATABASE if exists twitter_db;

CREATE DATABASE if not exists twitter_db;

USE twitter_db;

-- DROP TABLE if exists users;

CREATE TABLE users (
    id INT AUTO_INCREMENT,
    username VARCHAR(50) NOT NULL UNIQUE,
    email_address VARCHAR(50) NOT NULL UNIQUE,
    first_name VARCHAR(50) NOT NULL UNIQUE,
    last_name VARCHAR(50) NOT NULL UNIQUE,
    phone_number VARCHAR(50) UNIQUE,
    created_at TIMESTAMP DEFAULT (NOW()),
    updated_at TIMESTAMP DEFAULT (NOW()) ON UPDATE (NOW()),
    follower_count INT NOT NULL DEFAULT 0,
    PRIMARY KEY (id)
);

INSERT INTO users (username, email_address, first_name, last_name, phone_number) VALUES
('nachop51', 'nacho@gmail.com', 'Nacho', 'Peralta', '1234567890')
('johndoe', 'johndoe@gmail.com', 'John', 'Doe', '1234567891')
('janedoe', 'janedoe@gmail.com', 'Jane', 'Doe', '1234567892')
('user1', 'user@gmail.com', 'User', 'One', '1234567893')
('user2', 'user2@gmail.com', 'User', 'Two', '1234567894');

-- DROP TABLE if exists followers;

CREATE TABLE if not exists followers (
    follower_id INT,
    following_id INT,
    created_at TIMESTAMP DEFAULT (NOW()),
    FOREIGN KEY (follower_id) REFERENCES users(id),
    FOREIGN KEY (following_id) REFERENCES users(id),
    PRIMARY KEY (follower_id, following_id)
);

ALTER TABLE followers
ADD CONSTRAINT check_follower_id_not_equal_following_id
CHECK (follower_id <> following_id);

INSERT INTO followers(follower_id, following_id) VALUES
(1, 2),
(2, 1),
(3, 1),
(4, 1),
(3, 2),
(2, 3),
(2, 4);

-- SELECT follower_id, following_id FROM followers;
-- SELECT follower_id FROM followers WHERE following_id = 1;
-- SELECT COUNT(follower_id) FROM followers WHERE following_id = 1;

-- SELECT following_id, COUNT(follower_id) AS followers_count FROM followers
-- GROUP BY following_id
-- ORDER BY followers_count DESC
-- LIMIT 5;

SELECT users.id, users.username, following_id, COUNT(follower_id) AS followers_count
FROM followers
JOIN users ON users.id = followers.following_id
GROUP BY following_id
ORDER BY followers_count DESC
LIMIT 5;

-- DROP TABLE if exists tweets;

CREATE TABLE if not exists tweets (
    id INT AUTO_INCREMENT,
    created_at TIMESTAMP DEFAULT (NOW()),
    user_id INT,
    tweet_text VARCHAR(140) NOT NULL,
    num_likes INT DEFAULT 0,
    num_retweets INT DEFAULT 0,
    num_comments INT DEFAULT 0,
    FOREIGN KEY (user_id) REFERENCES users(id),
    PRIMARY KEY (id)
);

INSERT INTO tweets (user_id, tweet_text) VALUES
(1, 'Hello world, first tweet!'),
(2, 'Wohooooooooooooo!'),
(3, 'I love this twitter clone!'),
(1, 'Sunny day here!'),
(2, 'Papanamericano 🎶'),
(3, 'akjlsdslakdlsakdj!!!!'),
(1, '🐷🐷🐷');

-- SELECT user_id, COUNT(*) AS tweets_count FROM tweets
-- GROUP BY user_id;

SELECT id, tweet_text, user_id
FROM tweets
WHERE user_id IN (
    SELECT following_id
    FROM followers
    GROUP BY following_id
    HAVING COUNT(*) > 2
);

-- DELETE FROM tweets WHERE id = 1;
-- DELETE FROM tweets WHERE users_id = 1;

-- DELETE FROM tweets WHERE tweet_text LIKE '%kjlsdsla%';

-- UPDATE tweets SET num_comments = num_comments + 1
-- WHERE id = 2;

-- UPDATE tweets SET tweet_text = REPLACE(tweet_text, '🐷', '🐝')
-- WHERE tweet_text LIKE '%🐷%';

-- DROP TABLE if exists tweet_likes;

CREATE TABLE if not exists tweet_likes (
    user_id INT,
    tweet_id INT,
    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (tweet_id) REFERENCES tweets(id),
    PRIMARY KEY (user_id, tweet_id)
);

INSERT INTO tweet_likes (user_id, tweet_id) VALUES
(1, 2),
(2, 1),
(3, 1),
(4, 1),
(3, 2),
(2, 3),
(2, 4);

-- SELECT tweet_id, COUNT(*) AS like_count
-- FROM tweet_likes
-- GROUP BY tweet_id;

-- DROP TRIGGER if exists increase_follower_count;

DELIMITER $$
CREATE TRIGGER if not exists increase_follower_count
    AFTER INSERT ON followers
    FOR EACH ROW
    BEGIN
        UPDATE users
        SET follower_count = follower_count + 1
        WHERE id = NEW.following_id;
    END $$
DELIMITER ;

DELIMITER $$
CREATE TRIGGER if not exists decrease_follower_count
    AFTER DELETE ON followers
    FOR EACH ROW
    BEGIN
        UPDATE users
        SET follower_count = follower_count - 1
        WHERE id = NEW.following_id;
    END $$
DELIMITER ;
