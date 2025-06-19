from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

# SQLite データベース URL
SQLALCHEMY_DATABASE_URL = "sqlite:///./telemetry.db"

# SQLite3 の場合、同一スレッドで複数アクセスを許可するオプション
engine = create_engine(
    SQLALCHEMY_DATABASE_URL, connect_args={"check_same_thread": False}
)

# セッション生成関数
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()
