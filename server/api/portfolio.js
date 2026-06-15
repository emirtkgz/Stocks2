import express from "express"
import jwt from "jsonwebtoken"
import bcrypt from "bcryptjs"

import { authenticate } from "../auth.js"
import errors from "../errors/errors.json" with {type: 'json'}
import sql from "../sql.js"

const router = express.Router()

router.get('/data', async (req, res) => {
    authenticate(req, res, async (payload) => {
        const data = await sql`SELECT "Data" FROM "Portfolios" WHERE "Username" = ${payload.username}`

        res.send({...data[0], error: errors[0]})
    })
});

export default router