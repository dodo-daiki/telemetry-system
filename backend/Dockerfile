FROM python:3.11-slim

WORKDIR /app

# ビルドコンテキストは ./backend なので "backend/" を省略する！
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY app ./app
ENV PYTHONPATH=/app

EXPOSE 8000
CMD ["uvicorn", "app.main:app", "--host", "0.0.0.0", "--port", "8000"]
