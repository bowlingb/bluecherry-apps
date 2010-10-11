-- Media listings
CREATE TABLE Media (
	id integer PRIMARY KEY NOT NULL,
	start integer NOT NULL DEFAULT CURRENT_TIMESTAMP,
	end integer NOT NULL DEFAULT 0, -- 0 means in-progress
	device_id integer NOT NULL,
	container varchar(10) NOT NULL,
	video varchar(10) NOT NULL, -- e.g. m4v
	audio varchar(10) NOT NULL, -- e.g. mp3
	archive boolean NOT NULL DEFAULT FALSE,
	FOREIGN KEY (device_id) REFERENCES Devices(id)
                ON UPDATE CASCADE ON DELETE CASCADE
);
