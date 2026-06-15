// Configure .env
import dotenv from "dotenv"
dotenv.config()

import express from "express"
import postgres from "postgres";

// Import routers
import login from "./auth/login.js"
import register from "./auth/register.js"
import portfolio from "./api/portfolio.js"

// Login to database
import sql from "./sql.js"

// Create an Express App
const app = express();
app.use(express.json())

// --- Parse routers ---
app.use("/auth", login)
app.use("/auth", register)

app.use("/api/portfolio", portfolio)
// ---------------------

app.listen(process.env.PORT, async () => {
    console.log(`Server is on, listening on port ${process.env.PORT}`);
});