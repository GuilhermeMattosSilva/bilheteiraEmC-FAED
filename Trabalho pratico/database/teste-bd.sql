USE Bilheteira;
GO

INSERT INTO Users (user_name, email, NIF)
VALUES
('Guilherme Silva', 'guilherme@teste.com', '123456789');
GO

INSERT INTO Type_tickets (description, discount_percentage)
VALUES
('Normal', 0),
('Estudante', 20),
('Senior', 30);
GO