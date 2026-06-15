import postgres from "postgres"

// Connect to database
import credentials from "./cred.json" with {type: 'json'}
const sql = postgres(credentials)

// Check connection by pinging the database
try {
    await sql`SELECT 1`
    console.log('Connected to PostgreSQL successfully!')
} catch (error) {
    console.error('Failed the connection to PostgreSQL:', error.message)
}

export default sql