
IF DB_ID('AuctionsPortal') IS NOT NULL
	DROP DATABASE AuctionsPortal;
GO

CREATE DATABASE AuctionsPortal;
GO
USE AuctionsPortal;
GO

CREATE TABLE Advetiser (
	AdvetiserId INTEGER PRIMARY KEY IDENTITY(1,1),
	Name VARCHAR(30) NOT NULL,
	UserName VARCHAR(30) NOT NULL,
	Password VARCHAR(30) NOT NULL
);
GO

CREATE TABLE Users (
	UserId INTEGER PRIMARY KEY IDENTITY(1,1),
	Name VARCHAR(30) NOT NULL,
	Password VARCHAR(30) NOT NULL,
	UserName VARCHAR(30) NOT NULL,
	PhoneNumber VARCHAR(15),
	EMail VARCHAR(30)
);
GO

CREATE TABLE Category (
	CategoryId INTEGER PRIMARY KEY IDENTITY(1,1),
	CatgoryName VARCHAR(30)
);
GO

CREATE TABLE Item (
	ItemId INTEGER PRIMARY KEY IDENTITY(1,1),
	Name VARCHAR(30),
	CategoryId INTEGER NOT NULL,
	Description VARCHAR(200),
	StartingCall INTEGER NOT NULL,
	CloseDate DATE NOT NULL,
	CONSTRAINT ItemToCatgory 
        FOREIGN KEY (CategoryId) 
        REFERENCES Category (CategoryId)
	
);
GO

CREATE TABLE ItemImage
(
	ImageId INTEGER PRIMARY KEY IDENTITY(1,1),
	ItemId INTEGER NOT NULL,
	Image VARBINARY(max) NOT NULL
	CONSTRAINT ImageToItem 
        FOREIGN KEY (ItemId) 
        REFERENCES Item (ItemId)
);
GO

CREATE TABLE Bidding (
	ItemId INTEGER NOT NULL,
	AdvetiserId INTEGER NOT NULL,
	CallDate Date NOT NULL,
	UserId INTEGER,
	Amount INTEGER,
	CONSTRAINT BiddingToItem 
        FOREIGN KEY (ItemId) 
        REFERENCES Item (ItemId),
	CONSTRAINT BiddingToAdvatiser
        FOREIGN KEY (AdvetiserId) 
        REFERENCES Advetiser (AdvetiserId),
	CONSTRAINT BiddingToUser
        FOREIGN KEY (UserId) 
        REFERENCES Users (UserId),
	PRIMARY KEY (ItemId)
	
);
GO

insert into Category values ('B�tor');
insert into Category values ('Hangszer');
insert into Category values ('J�t�k');
insert into Category values ('Elektroinika');
insert into Category values ('�kszer');

insert into Item values ('L�mpa',1,'Sz�p l�mpa. Vedd meg, mert zs�r!!',500,'2016-12-11');
insert into Item values ('Asztal',1,'Sz�p asztal. Vedd meg, mert zs�r!!',1000,'2016-12-11');
insert into Item values ('Szekr�ny',1,'Sz�p szekr�ny. Vedd meg, mert zs�r!!',2000,'2016-12-11');
insert into Item values ('Sz�k',1,'Sz�p szekr�ny. Vedd meg, mert zs�r!!',700,'2016-12-11');
insert into Item values ('Ajt�',1,'Sz�p ajt�. Vedd meg, mert zs�r!!',3000,'2016-12-11');
insert into Item values ('Szekr�ny',1,'Sz�p szekr�ny. Vedd meg, mert zs�r!!',2000,'2016-12-11');
insert into Item values ('Git�r',2,'Sz�p git�r. Vedd meg, mert zs�r!!',3057,'2016-12-23');
insert into Item values ('Zongora',2,'Sz�p zongora. Vedd meg, mert zs�r!!',1000,'2016-12-11');
insert into Item values ('Dob',2,'Sz�p dob. Vedd meg, mert zs�r!!',2000,'2016-12-11');
insert into Item values ('Heged�',2,'Sz�p heged�. Vedd meg, mert zs�r!! Sherlock is ilyet haszn�l.',10000,'2017-10-11');
insert into Item values ('S�p',2,'Sz�p s�p. Vedd meg, mert zs�r!!',450,'2016-4-11');
insert into Item values ('Harmonika',2,'Sz�p harmonika. Vedd meg, mert zs�r!!',600,'2016-12-11');
insert into Item values ('Kisaut�',3,'Sz�p kisaut�. Vedd meg, mert zs�r!!',500,'2016-12-11');
insert into Item values ('J�t�kkatona',3,'Sz�p kis j�t�kkatona. Vedd meg, mert zs�r!!',250,'2016-7-11');
insert into Item values ('Sz�nez�',3,'Sz�p z�nez�. Ki�lheted rajta a kreativit�sod.',1500,'2016-6-11');
insert into Item values ('Monitor',4,'Sz�p monitor. Vedd meg, mert zs�r!!',5000,'2016-12-11');
insert into Item values ('Billenyt�zet',4,'Sz�p klaviat�ra. Vedd meg, mert zs�r!!',3000,'2016-12-11');
insert into Item values ('Hangfal',4,'Sz�p hangfal. Vedd meg, mert zs�r!!',5000,'2016-12-11');
insert into Item values ('Eg�r',4,'Sz�p eg�r. Vedd meg, mert zs�r!!',1000,'2016-12-11');
insert into Item values ('LG TV',4,'HD TV. Mozimin�s�g!! Vedd meg, mert zs�r!!',1000,'2016-12-11');
insert into Item values ('Elektromos borotva',4,'Sz�p borotva. Kirlyul v�gja a szak�llad. Vedd meg, mert zs�r!!',2000,'2016-12-11');
insert into Item values ('Gy�r�',5,'Sz�p gy�r�. Vedd meg, mert zs�r!!',500,'2016-12-11');
insert into Item values ('Nyakl�nc',5,'Sz�p nyakl�nc. Vedd meg, mert zs�r!!',1000,'2016-12-11');
insert into Item values ('F�lbeval�',5,'Sz�p f�lbeval�. Vedd meg, mert zs�r!!',2000,'2016-12-11');
insert into Item values ('Kir�ly kark�t�',5,'Sz�p kark�t�. Vedd meg, mert zs�r!!',500,'2016-12-11');
insert into Item values ('Csini gy�r�',5,'M�gszebb gy�r�. Vedd meg, mert zs�r!!',1000,'2016-12-11');
insert into Item values ('A legcsinibb gy�r�',5,'Nincs jobb gy�r� enn�l. Vedd meg, mert zs�r!!',5000,'2017-4-11');


insert into Advetiser values ('Nagy Andr�s','na','123456');

insert into Users values ('P�li D�niel','123456','pd','+36-30/4301237','palidani@inf.elte.hu');
insert into Users values ('Noll P�ter','123456','np','+36-30/9437969','nollpeti@inf.elte.hu');

insert into Bidding values (1,1,'2016-11-11',null,null);
insert into Bidding values (2,1,'2016-11-11',null,null);
insert into Bidding values (3,1,'2016-11-11',null,null);
insert into Bidding values (4,1,'2016-11-11',null,null);
insert into Bidding values (5,1,'2016-11-11',null,null);
insert into Bidding values (6,1,'2016-11-11',null,null);
insert into Bidding values (7,1,'2016-11-11',null,null);
insert into Bidding values (8,1,'2016-11-11',null,null);
insert into Bidding values (9,1,'2016-11-11',null,null);
insert into Bidding values (10,1,'2016-11-11',null,null);
insert into Bidding values (11,1,'2016-11-11',null,null);
insert into Bidding values (12,1,'2016-11-11',null,null);
insert into Bidding values (13,1,'2016-11-11',null,null);
insert into Bidding values (14,1,'2016-11-11',null,null);
insert into Bidding values (15,1,'2016-11-11',null,null);
insert into Bidding values (16,1,'2016-11-11',null,null);
insert into Bidding values (17,1,'2016-11-11',null,null);
insert into Bidding values (18,1,'2016-11-11',null,null);
insert into Bidding values (19,1,'2016-11-11',null,null);
insert into Bidding values (20,1,'2016-11-11',null,null);
insert into Bidding values (21,1,'2016-11-11',null,null);
insert into Bidding values (22,1,'2016-11-11',null,null);
insert into Bidding values (23,1,'2016-11-11',null,null);
insert into Bidding values (24,1,'2016-11-11',null,null);
insert into Bidding values (25,1,'2016-11-11',null,null);
insert into Bidding values (26,1,'2016-11-11',null,null);
insert into Bidding values (27,1,'2016-11-11',null,null);

GO