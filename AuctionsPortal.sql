
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

CREATE TABLE Users (
	UserID INTEGER PRIMARY KEY IDENTITY(1,1),
	Name VARCHAR(30) NOT NULL,
	UserName VARCHAR(30) NOT NULL,
	PhoneNumber INTEGER,
	EMail VARCHAR(30)
);

CREATE TABLE Catgory (
	CagoryID INTEGER PRIMARY KEY IDENTITY(1,1),
	CatgoryName VARCHAR(30)
);

CREATE TABLE Item (
	ItemID INTEGER PRIMARY KEY IDENTITY(1,1),
	Name VARCHAR(30),
	CagoryID INTEGER NOT NULL,
	Description VARCHAR(100),
	StartingCall INTEGER NOT NULL,
	CloseDate DATE,
	Image VARBINARY(max) NOT NULL
	CONSTRAINT ItemToCatgory 
        FOREIGN KEY (CagoryID) 
        REFERENCES Catgory (CagoryID)
	
);

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
