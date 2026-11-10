CREATE DATABASE Bilheteira;
GO

USE Bilheteira;
GO

CREATE TABLE Users (
    id_user INT IDENTITY(1,1) PRIMARY KEY,
    user_name VARCHAR(100) NOT NULL UNIQUE,
    email VARCHAR(150) NOT NULL UNIQUE,
    NIF CHAR(9) NOT NULL UNIQUE,
    role VARCHAR(20) NOT NULL DEFAULT 'USER'
);

CREATE TABLE Shows (
    id_show INT IDENTITY(1,1) PRIMARY KEY,
    show_name VARCHAR(150) NOT NULL,
    location VARCHAR(150) NOT NULL,
    show_date DATETIME NOT NULL,
    price_ticket DECIMAL(10,2) NOT NULL
);

CREATE TABLE Type_tickets (
    id_type INT IDENTITY(1,1) PRIMARY KEY,
    description VARCHAR(100) NOT NULL,
    discount_percentage DECIMAL(5,2) NOT NULL
);

CREATE TABLE Tickets (
    id_ticket INT IDENTITY(1,1) PRIMARY KEY,
    id_user INT NOT NULL,
    id_show INT NOT NULL,
    id_type INT NOT NULL,
    quantity INT NOT NULL CHECK(quantity > 0),

    CONSTRAINT FK_Tickets_Users
        FOREIGN KEY (id_user)
        REFERENCES Users(id_user),

    CONSTRAINT FK_Tickets_Shows
        FOREIGN KEY (id_show)
        REFERENCES Shows(id_show),

    CONSTRAINT FK_Tickets_TypeTickets
        FOREIGN KEY (id_type)
        REFERENCES Type_tickets(id_type)
);

CREATE TABLE Receipts (
    id_receipt INT IDENTITY(1,1) PRIMARY KEY,
    id_ticket INT NOT NULL UNIQUE,
    value DECIMAL(10,2) NOT NULL,
    date_emission DATETIME NOT NULL DEFAULT GETDATE(),

    CONSTRAINT FK_Receipts_Tickets
        FOREIGN KEY (id_ticket)
        REFERENCES Tickets(id_ticket)
);