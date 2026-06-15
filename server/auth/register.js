import express from "express"
import bcrypt from "bcryptjs"

import errors from "../errors/errors.json" with {type: 'json'}
import sql from "../sql.js"

const router = express.Router()

/* 
 * Implement register requests
 * Request body should look like {"username": username, "password": password}
*/
router.post("/register", async (req, res) => {
    const username = req.body["username"]
    const password = req.body["password"]

    // Check if username and password are correctly provided
    if(!username || !password) {
        res.status(400).json({error: errors[5]})
    }

    // Check if username already exists
    var userExists = await sql`SELECT EXISTS(SELECT 1 FROM "Users" WHERE "Username" = ${username})`
    if(userExists) {
        res.status(400).json({error: errors[1]})
    }

    // Generate a 10 iteration salt for the user
    const salt = bcrypt.genSaltSync(10)
    // And generate the hash from password + salt
    const hash = bcrypt.hashSync(password, salt)

    // Insert the hash into DB (No need to insert the salt since hash already contains it)
    await sql`INSERT INTO "Users" ("Username", "Password_Hash") VALUES (${username}, ${hash})`

    res.status(200).json({error: errors[0]})
})

export default router