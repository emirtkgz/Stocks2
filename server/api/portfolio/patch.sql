-- $1: Username
-- $2: Json Data

UPDATE "Portfolios"
SET "Data" = (
    SELECT jsonb_agg(
        CASE
            WHEN elem->>'name' = $2::jsonb->>'name'
            THEN elem || $2::jsonb
            ELSE elem
        END
    )
    FROM jsonb_array_elements("Data") AS elem
)
WHERE "Username" = $1
AND EXISTS (
    SELECT 1
    FROM jsonb_array_elements("Data") AS elem
    WHERE elem->>'name' = $2::jsonb->>'name'
);