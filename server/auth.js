import jwt from 'jsonwebtoken';

import errors from "./errors/errors.json" with {type: 'json'}

// Confirm the authenticity of the JWT
export function authenticate(req, res, next) {
    // Authorization: Bearer <token>
    const authHeader = req.headers.authorization;
    const token = authHeader?.split(' ')[1]; // Get rid of the Bearer part

    if (!token)
        return res.status(401).json({error: errors[3]});

    try {
        const payload = jwt.verify(token, process.env.JWT_PRIVATE_KEY);
        next(payload);
    } 
    catch (err) {
        if (err.name === 'TokenExpiredError')
            return res.status(401).json({error: errors[4]});
        
        return res.status(403).json({error: errors[3]});
    }
}