from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.orm import Session
from app import schemas, crud
from app.database import get_db

router = APIRouter(tags=["uplink_command"])

@router.post("/uplink_command", response_model=schemas.UplinkCommandOut)
def post_uplink_command(
    command: schemas.UplinkCommandCreate,
    db: Session = Depends(get_db)
):
    try:
        return crud.create_uplink_command(db, command)
    except Exception as e:
        raise HTTPException(status_code=500, detail=f"Failed to register command: {e}")
