from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
from typing import List
import uvicorn

app = FastAPI()

# CORS Configuration
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

class Entity(BaseModel):
    id: int
    x: float
    y: float
    z: float
    type: str
    health: int = 0

class GameState(BaseModel):
    timestamp: float
    entities: List[Entity]

# Mock database
game_data = []

@app.post("/api/update")
async def update_data(state: GameState):
    global game_data
    game_data = state.entities
    return {"status": "success", "entities_received": len(game_data)}

@app.get("/api/entities")
async def get_entities():
    return {
        "count": len(game_data),
        "entities": game_data,
        "last_updated": game_data[-1].timestamp if game_data else None
    }

@app.get("/api/entities/{entity_id}")
async def get_entity(entity_id: int):
    try:
        return next(e for e in game_data if e.id == entity_id)
    except StopIteration:
        raise HTTPException(status_code=404, detail="Entity not found")

if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8000)
