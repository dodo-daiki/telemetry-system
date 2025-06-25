from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session
from app import schemas, crud
from app.database import get_db

router = APIRouter(tags=["uplink_log"])

@router.get("/uplink_log", response_model=list[schemas.UplinkCommandOut])
def get_uplink_logs(db: Session = Depends(get_db)):
    return crud.get_all_uplink_commands(db)
