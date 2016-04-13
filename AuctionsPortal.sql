
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
	Name VARCHAR(40) NOT NULL,
	Password BINARY(64) NOT NULL,
	UserName VARCHAR(30) NOT NULL,
	PhoneNumber VARCHAR(15) NOT NULL,
	EMail VARCHAR(30) NOT NULL
);
GO

CREATE TABLE Category (
	CategoryId INTEGER PRIMARY KEY IDENTITY(1,1),
	CatgoryName VARCHAR(30)
);
GO

CREATE TABLE Item (
	ItemId INTEGER PRIMARY KEY IDENTITY(1,1),
	Name VARCHAR(30) NOT NULL,
	CategoryId INTEGER NOT NULL,
	AdvetiserId INTEGER NOT NULL,
	Description VARCHAR(200),
	StartingCall INTEGER NOT NULL,
	CloseDate DATE NOT NULL,
	CONSTRAINT ItemToCatgory 
        FOREIGN KEY (CategoryId) 
        REFERENCES Category (CategoryId),
	CONSTRAINT ItemToAdvatiser
        FOREIGN KEY (AdvetiserId) 
        REFERENCES Advetiser (AdvetiserId)
	
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
	BiddingId INTEGER PRIMARY KEY IDENTITY(1,1),
	ItemId INTEGER NOT NULL,
	CallDate Date NOT NULL,
	UserId INTEGER,
	Amount INTEGER,
	CONSTRAINT BiddingToItem 
        FOREIGN KEY (ItemId) 
        REFERENCES Item (ItemId),
	CONSTRAINT BiddingToUser
        FOREIGN KEY (UserId) 
        REFERENCES Users (UserId)
	
);
GO

insert into Category values ('Bútor');
insert into Category values ('Hangszer');
insert into Category values ('Játék');
insert into Category values ('Elektroinika');
insert into Category values ('Ékszer');

insert into Advetiser values ('Nagy András','na','123456');

insert into Item values ('Lámpa',1,1,'Szép lámpa. Vedd meg, mert zsír!!',500,'2016-12-11');
insert into Item values ('Asztal',1,1,'Szép asztal. Vedd meg, mert zsír!!',1000,'2016-12-11');
insert into Item values ('Szekrény',1,1,'Szép szekrény. Vedd meg, mert zsír!!',2000,'2016-12-11');
insert into Item values ('Szék',1,1,'Szép szekrény. Vedd meg, mert zsír!!',700,'2016-12-11');
insert into Item values ('Ajtó',1,1,'Szép ajtó. Vedd meg, mert zsír!!',3000,'2016-12-11');
insert into Item values ('Szekrény',1,1,'Szép szekrény. Vedd meg, mert zsír!!',2000,'2016-12-11');
insert into Item values ('Gitár',2,1,'Szép gitár. Vedd meg, mert zsír!!',3057,'2016-12-23');
insert into Item values ('Zongora',2,1,'Szép zongora. Vedd meg, mert zsír!!',1000,'2016-12-11');
insert into Item values ('Dob',2,1,'Szép dob. Vedd meg, mert zsír!!',2000,'2016-12-11');
insert into Item values ('Hegedû',2,1,'Szép hegedû. Vedd meg, mert zsír!! Sherlock is ilyet használ.',10000,'2017-10-11');
insert into Item values ('Síp',2,1,'Szép síp. Vedd meg, mert zsír!!',450,'2016-4-11');
insert into Item values ('Harmonika',2,1,'Szép harmonika. Vedd meg, mert zsír!!',600,'2016-12-11');
insert into Item values ('Kisautó',3,1,'Szép kisautó. Vedd meg, mert zsír!!',500,'2016-12-11');
insert into Item values ('Játékkatona',3,1,'Szép kis játékkatona. Vedd meg, mert zsír!!',250,'2016-7-11');
insert into Item values ('Színezõ',3,1,'Szép zínezõ. Kiélheted rajta a kreativitásod.',1500,'2016-6-11');
insert into Item values ('Monitor',4,1,'Szép monitor. Vedd meg, mert zsír!!',5000,'2016-12-11');
insert into Item values ('Billenytûzet',4,1,'Szép klaviatúra. Vedd meg, mert zsír!!',3000,'2016-12-11');
insert into Item values ('Hangfal',4,1,'Szép hangfal. Vedd meg, mert zsír!!',5000,'2016-12-11');
insert into Item values ('Egér',4,1,'Szép egér. Vedd meg, mert zsír!!',1000,'2016-12-11');
insert into Item values ('LG TV',4,1,'HD TV. Moziminõség!! Vedd meg, mert zsír!!',1000,'2016-12-11');
insert into Item values ('Elektromos borotva',4,1,'Szép borotva. Kirlyul vágja a szakállad. Vedd meg, mert zsír!!',2000,'2016-12-11');
insert into Item values ('Gyûrû',5,1,'Szép gyûrû. Vedd meg, mert zsír!!',500,'2016-12-11');
insert into Item values ('Nyaklánc',5,1,'Szép nyaklánc. Vedd meg, mert zsír!!',1000,'2016-12-11');
insert into Item values ('Fülbevaló',5,1,'Szép fülbevaló. Vedd meg, mert zsír!!',2000,'2016-12-11');
insert into Item values ('Király karkötõ',5,1,'Szép karkötõ. Vedd meg, mert zsír!!',500,'2016-12-11');
insert into Item values ('Csini gyûrû',5,1,'Mégszebb gyûrû. Vedd meg, mert zsír!!',1000,'2016-12-11');
insert into Item values ('A legcsinibb gyûrû',5,1,'Nincs jobb gyûrû ennél. Vedd meg, mert zsír!!',5000,'2017-4-11');


GO