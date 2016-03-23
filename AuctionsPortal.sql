
IF DB_ID('AuctionsPortal') IS NOT NULL
	DROP DATABASE AuctionsPortal;
GO

CREATE DATABASE AuctionsPortal;
GO
USE AuctionsPortal;
GO

CREATE TABLE Advetiser(
	AdvetiserId INTEGER PRIMARY KEY IDENTITY(1,1),
	Name VARCHAR(30) NOT NULL,
	UserName VARCHAR(30) NOT NULL,
	Password VARCHAR(30) NOT NULL
);
GO

CREATE TABLE Users (
	UserID INTEGER PRIMARY KEY IDENTITY(1,1),
	Name VARCHAR(30) NOT NULL,
	UserName VARCHAR(30) NOT NULL,
	PhoneNumber INTEGER,
	EMail VARCHAR(30)
);
GO

CREATE TABLE Catgory (
	CagoryID INTEGER PRIMARY KEY IDENTITY(1,1),
	CatgoryName VARCHAR(30)
);
GO

CREATE TABLE Item (
	ItemID INTEGER PRIMARY KEY IDENTITY(1,1),
	Name VARCHAR(30),
	CagoryID INTEGER NOT NULL,
	Description VARCHAR(100),
	StartingCall INTEGER NOT NULL,
	CloseDate DATE,
	CONSTRAINT ItemToCatgory 
        FOREIGN KEY (CagoryID) 
        REFERENCES Catgory (CagoryID)
	
);
GO

CREATE TABLE ItemImage
(
	ImageID INTEGER PRIMARY KEY IDENTITY(1,1),
	ItemID INTEGER NOT NULL,
	ImageS VARBINARY(max) NOT NULL
	CONSTRAINT ImageToitem 
        FOREIGN KEY (ItemID) 
        REFERENCES Item (ItemID)
);
GO

CREATE TABLE Bidding (
	BiddingID INTEGER PRIMARY KEY IDENTITY(1,1) NOT NULL,
	ItemID INTEGER NOT NULL,
	UserID INTEGER NOT NULL,
	Amount INTEGER NOT NULL,
	CallDate Date
	CONSTRAINT BiddingToItem 
        FOREIGN KEY (ItemID) 
        REFERENCES Item (ItemID),
	CONSTRAINT BiddingToUser
        FOREIGN KEY (UserID) 
        REFERENCES Users (UserID)
	
);
GO

insert into Catgory values ('Bútor');
insert into Catgory values ('Hangszer');
insert into Catgory values ('Ékszer');

insert into Item values ('Lámpa',1,'Szép lámpa',500,null);
insert into Item values ('Asztal',1,'Szép asztal',1000,null);
insert into Item values ('Szekrény',1,'Szép szekrény',2000,null);


insert into Users values ('Nagy András', 'na',0630,'nagyandras95@inf.elte.hu');

insert into Bidding values (1,1,500,'2016-11-11');
insert into Bidding values (2,1,500,'2016-11-11');
insert into Bidding values (3,1,500,'2016-11-11');

GO