-- 1 .
-- Sans index 
SELECT * FROM film WHERE id=5200; --

-- Avec index
CREATE UNIQUE INDEX idx_film ON film(id);
SELECT * FROM film WHERE id=5200;