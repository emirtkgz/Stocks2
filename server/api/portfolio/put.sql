-- $1: Username
-- $2: Json Data

UPDATE "Portfolios"
SET "Data" = (
    SELECT CASE
        -- If ticker already exists: sum amounts, calculate weighted average price
        WHEN EXISTS (
            SELECT 1 FROM jsonb_array_elements("Data") AS elem
            WHERE elem->>'name' = ($2::jsonb)->>'name'
        )
        THEN (
            SELECT jsonb_agg(
                CASE
                    WHEN elem->>'name' = ($2::jsonb)->>'name'
                    THEN elem || jsonb_build_object(
                        'amount',    (elem->>'amount')::numeric + ($2::jsonb->>'amount')::numeric,
                        'avg_price', (
                            (elem->>'avg_price')::numeric      * (elem->>'amount')::numeric +
                            ($2::jsonb->>'avg_price')::numeric * ($2::jsonb->>'amount')::numeric
                        ) / (
                            (elem->>'amount')::numeric + ($2::jsonb->>'amount')::numeric
                        )
                    )
                    ELSE elem
                END
            )
            FROM jsonb_array_elements("Data") AS elem
        )
        -- If ticker doesn't exist: append the new entry
        ELSE "Data" || $2::jsonb
    END
)
WHERE "Username" = $1;