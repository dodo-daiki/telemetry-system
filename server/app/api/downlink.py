from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.orm import Session
from app import schemas, crud, database, models

router = APIRouter()

# DBセッション依存性
def get_db():
    db = database.SessionLocal()
    try:
        yield db
    finally:
        db.close()

@router.post("/downlink_data", response_model=schemas.TelemetryLogResponse)
def post_downlink_data(data: schemas.DownlinkData, db: Session = Depends(get_db)):
    try:
        existing = db.query(models.TelemetryLog).filter_by(timestamp=data.timestamp).first()
        if existing:
            raise HTTPException(status_code=409, detail="Duplicate telemetry data with same timestamp.")
        entry = crud.create_telemetry_log(db, data)
        return entry  # ← FastAPIが自動的に Pydantic モデルに変換
    except Exception as e:
        raise HTTPException(status_code=400, detail=f"Failed to store telemetry: {e}")
