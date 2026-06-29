import express from "express"
import jwt from "jsonwebtoken"
import bcrypt from "bcryptjs"

import errors from "../errors/errors.json" with {type: 'json'}
import sql from "../sql.js"

const router = express.Router()

/* 
 * Implement login requests
 * Request body should look like {"username": username, "password": password}
*/
// TODO: Test for wrong inputs
router.post("/login", async (req, res) => {
    const username = req.body["username"]
    const password = req.body["password"]

    // Check if username and password are correctly provided
    if(!username || !password) {
        res.status(400).json({error: errors[5]})
        return
    }

    // Check if user exists
    var userExists = (await sql`SELECT EXISTS(SELECT 1 FROM "Users" WHERE "Username" = ${username})`)[0]["exists"]
    if(!userExists) {
        res.status(400).json({error: errors[2]})
        return
    }

    // Get user password hash and check if it is correct
    const [{Password_Hash: hash}] = await sql`SELECT "Password_Hash" FROM "Users" WHERE "Username" = ${username}`
    
    var isCorrectPassword = bcrypt.compareSync(password, hash)
    if(!isCorrectPassword) {
        res.status(400).json({error: errors[2]})
        return
    }

    // Create a Json Web Token once everything is correct
    const token = jwt.sign(
        {username: username},
        process.env.JWT_PRIVATE_KEY,
        {expiresIn: process.env.JWT_ACCESS_TIMEOUT}
    )

    res.status(200).json({accessToken: token, error: errors[0]})
})

export default router