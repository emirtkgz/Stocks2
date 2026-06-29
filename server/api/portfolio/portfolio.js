import express from "express"
import jwt from "jsonwebtoken"
import bcrypt from "bcryptjs"

import { authenticate } from "../../auth.js"
import errors from "../../errors/errors.json" with {type: 'json'}
import sql from "../../sql.js"

const router = express.Router()

// Queries the data
router.get('/data', async (req, res) => {
    authenticate(req, res, async (payload) => {
        const data = await sql`SELECT "Data" 
                               FROM "Portfolios" 
                               WHERE "Username" = ${payload.username}`

        res.send({...data[0], error: errors[0]})
    })
});


// Patches the current data with the provided one
router.patch('/data', async (req, res) => {
    authenticate(req, res, async (payload) => {
        if(!req.body) {
            res.status(400).json({error: errors[5]})
            return
        }

        await sql.file("./api/portfolio/patch.sql", [payload.username, req.body])

        res.status(200).json({error: errors[0]})
    })
});

// Deletes the entry by index
router.delete('/data', async (req, res) => {
    authenticate(req, res, async (payload) => {
        const {index} = req.query

        await sql`UPDATE "Portfolios" 
                  SET "Data" = "Data" - ${index}::int
                  WHERE "Username" = ${payload.username}`

        res.status(200).json({error: errors[0]})
    })
});

// Puts a new entry
router.put('/data', async (req, res) => {
    authenticate(req, res, async (payload) => {
        await sql.file("./api/portfolio/put.sql", [payload.username, req.body])

        res.status(200).json({error: errors[0]})
    })
});

export default router