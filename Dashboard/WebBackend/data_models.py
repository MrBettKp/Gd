from pydantic import BaseModel
from typing import Optional

class Vector3(BaseModel):
    x: float
    y: float
    z: float

class Entity(BaseModel):
    id: int
    position: Vector3
    type: str
    health: Optional[int] = None
    team: Optional[str] = None

class GameStateUpdate(BaseModel):
    timestamp: float
    entities: list[Entity]
    map_name: str
    game_time: float
