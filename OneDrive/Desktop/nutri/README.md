# 🧠 MindfulAI — AI-Powered Mental Health Awareness & Suicide Prevention Agent

> **Powered by IBM Watsonx.ai | IBM Granite Models | Python Flask | RAG Pipeline**

[![Python 3.10+](https://img.shields.io/badge/Python-3.10+-blue.svg)](https://python.org)
[![Flask](https://img.shields.io/badge/Flask-3.x-green.svg)](https://flask.palletsprojects.com)
[![IBM Watsonx.ai](https://img.shields.io/badge/IBM-Watsonx.ai-blue.svg)](https://www.ibm.com/watsonx)
[![IBM Granite](https://img.shields.io/badge/IBM-Granite--3.3--8B-purple.svg)](https://www.ibm.com/granite)

---

## ⚠️ Important Disclaimer

> **MindfulAI is an AI companion for emotional support and mental health awareness only.**  
> It is **NOT** a substitute for professional medical advice, diagnosis, or treatment.  
> If you or someone you know is in crisis, please call a helpline immediately.  
> 🇮🇳 **iCall:** 9152987821 · 🇺🇸 **988 Lifeline:** 988 · 🌍 **Crisis Text:** HOME to 741741

---

## 🌟 Features

### 🤖 AI Agent
- **Empathetic conversations** powered by IBM Granite 3.3-8B via Watsonx.ai
- **Risk classification** (Low / Moderate / High) using keyword-based RAG screening
- **RAG pipeline** enriches every AI response with relevant self-care resources
- **Crisis response** — immediate helpline display when high-risk language detected
- **Customisable AGENT_INSTRUCTIONS** — full personality, tone, safety, and behaviour control

### 📊 Dashboard
- **Daily Mood Tracker** with emoji mood selector
- **Weekly Emotional Trend Chart** (Chart.js line graph)
- **Mood Distribution Chart** (doughnut chart)
- **Wellness Score** (0–100, derived from mood history)
- **Stress Level Indicator** (Low / Moderate / High)
- **Positive Streak Counter** (consecutive good days)
- **Mood History Timeline** (last 10 entries)
- **Self-Care Progress** tracker (daily checklist)

### 📓 Emotion Journal
- Private, session-stored journal entries
- AI-powered emotional insight for each entry
- Risk level analysis per entry
- Journal history with search

### 🌱 Self-Care Resources
- 5 breathing techniques with step-by-step guides
- 5 mindfulness exercises
- 9 sleep improvement tips
- 10 mental health facts
- 15 positive affirmations
- Daily wellness tips

### 🆘 Emergency Support
- Worldwide crisis helplines (India, USA, UK, worldwide)
- Crisis safety plan steps
- Warning signs education
- Trusted contacts saver

### 🎨 UI/UX
- Calming blue-teal-green glassmorphism design
- Dark mode with smooth transitions
- Fully responsive (mobile-first)
- Bootstrap 5 + Font Awesome 6 + Chart.js
- Smooth animations and micro-interactions

---

## 🏗️ Project Structure

```
mindfulai/
├── app.py                          # Flask backend (main entry point)
├── requirements.txt                # Python dependencies
├── .env                            # Environment variables (NOT in git)
├── .env.example                    # Template for .env
├── README.md                       # This file
│
├── data/
│   └── mental_health_resources.json    # Self-care dataset (RAG knowledge base)
│
├── templates/
│   └── index.html                  # Single-page application template
│
└── static/
    ├── css/
    │   └── style.css               # Complete UI stylesheet
    └── js/
        └── app.js                  # Frontend JavaScript
```

---

## 🚀 Quick Start

### 1. Clone / Download the project

```bash
git clone <your-repo-url>
cd mindfulai
```

### 2. Create a virtual environment

```bash
# Windows
python -m venv myenv
myenv\Scripts\activate

# macOS / Linux
python3 -m venv myenv
source myenv/bin/activate
```

### 3. Install dependencies

```bash
pip install -r requirements.txt
```

### 4. Configure environment variables

```bash
cp .env.example .env
```

Edit `.env` with your real credentials:

```env
IBM_API_KEY=your_ibm_cloud_api_key_here
WATSONX_PROJECT_ID=your_watsonx_project_id_here
WATSONX_URL=https://us-south.ml.cloud.ibm.com
GRANITE_MODEL_ID=ibm/granite-3-3-8b-instruct
FLASK_SECRET_KEY=your-secret-key-here
FLASK_ENV=development
PORT=5000
```

### 5. Get IBM Credentials

**IBM Cloud API Key:**
1. Go to [https://cloud.ibm.com/iam/apikeys](https://cloud.ibm.com/iam/apikeys)
2. Click **Create an IBM Cloud API key**
3. Copy the key and add it to `.env` as `IBM_API_KEY`

**Watsonx.ai Project ID:**
1. Go to [https://dataplatform.cloud.ibm.com](https://dataplatform.cloud.ibm.com)
2. Create a new project (or use existing)
3. Go to **Project Settings → General → Project ID**
4. Copy and add to `.env` as `WATSONX_PROJECT_ID`

### 6. Run the application

```bash
# Development
python app.py

# OR with Flask CLI
flask run --debug

# Production (Gunicorn)
gunicorn -w 2 -b 0.0.0.0:5000 app:app
```

Open your browser: **http://localhost:5000**

---

## 🧩 Agent Customisation (`AGENT_INSTRUCTIONS`)

The `AGENT_INSTRUCTIONS` dictionary in [`app.py`](app.py) gives you full control:

```python
AGENT_INSTRUCTIONS = {
    "identity": {
        "name": "MindfulAI",              # Change the agent's name
        "tone": "warm, calm, empathetic", # Adjust tone
        "greeting": "Hello! ...",         # Custom greeting
    },
    "empathy": {
        "level": "very_high",             # low | medium | high | very_high
        "validate_feelings_first": True,
    },
    "safety": {
        "disclaimer": "...",              # Shown throughout the app
        "show_emergency_on_high_risk": True,
    },
    "risk_classification": { ... },       # Customise risk thresholds
    "crisis_response": { ... },           # Crisis behaviour
    "supported_languages": ["English", "Hindi", ...],
    "system_prompt_template": """...""",  # Full system prompt
}
```

---

## 🔬 RAG Pipeline

The RAG (Retrieval-Augmented Generation) pipeline works as follows:

```
User Message
     │
     ▼
┌─────────────────────────┐
│  Risk Classification     │  ← Keyword screening (High/Moderate/Low)
│  (classify_risk)         │
└─────────────────────────┘
     │
     ▼
┌─────────────────────────┐
│  Resource Retrieval      │  ← Select relevant resources from dataset
│  (rag_retrieve)          │    • Self-care activities (risk-matched)
│                          │    • Breathing techniques (if anxiety/stress)
│                          │    • Mindfulness exercises (if relevant)
│                          │    • Sleep tips (if sleep mentioned)
│                          │    • Emergency helplines (if high-risk)
└─────────────────────────┘
     │
     ▼
┌─────────────────────────┐
│  Prompt Construction     │  ← System prompt + RAG context + chat history
└─────────────────────────┘
     │
     ▼
┌─────────────────────────┐
│  IBM Granite Inference   │  ← IBM Watsonx.ai API call
│  (run_agent)             │
└─────────────────────────┘
     │
     ▼
Structured Response:
  { response, risk_level, risk_label, risk_color, show_emergency }
```

---

## 🌍 API Endpoints

| Method | Endpoint | Description |
|--------|----------|-------------|
| GET    | `/`           | Main SPA |
| POST   | `/api/chat`   | AI chat with risk classification + RAG |
| POST   | `/api/mood`   | Log mood entry, get updated analytics |
| GET    | `/api/mood/history` | Mood history + metrics |
| POST   | `/api/journal` | Save journal, get AI insight |
| GET    | `/api/journal/history` | All journal entries |
| GET    | `/api/affirmation` | Today's affirmation + wellness tip |
| GET    | `/api/resources` | All self-care resources |
| GET    | `/api/dashboard` | Dashboard data (all metrics) |
| GET    | `/api/health`  | Health check / status |

---

## ☁️ Deployment

### Render.com (Free)

1. Push code to GitHub
2. Go to [render.com](https://render.com) → New → Web Service
3. Connect your GitHub repo
4. Set **Build Command:** `pip install -r requirements.txt`
5. Set **Start Command:** `gunicorn -w 2 -b 0.0.0.0:$PORT app:app`
6. Add environment variables (IBM_API_KEY, WATSONX_PROJECT_ID, etc.)

### IBM Code Engine

```bash
# Build and push Docker image
docker build -t mindfulai .
docker push your-registry/mindfulai

# Deploy to IBM Code Engine
ibmcloud ce application create \
  --name mindfulai \
  --image your-registry/mindfulai \
  --env IBM_API_KEY=xxx \
  --env WATSONX_PROJECT_ID=xxx
```

### Docker

```bash
# Create Dockerfile (minimal example)
docker build -t mindfulai .
docker run -p 5000:5000 \
  -e IBM_API_KEY=xxx \
  -e WATSONX_PROJECT_ID=xxx \
  mindfulai
```

---

## 🛡️ Ethical AI Principles

This application is built with the following ethical principles:

1. **Never encourages self-harm** — safety rules are non-negotiable in AGENT_INSTRUCTIONS
2. **Always empathetic** — validates feelings before offering advice
3. **Crisis escalation** — high-risk detection triggers immediate helpline display
4. **Clear disclaimer** — prominently displayed throughout the app
5. **User privacy** — sessions are local; no data shared with third parties
6. **Non-judgmental** — compassionate, inclusive, and person-first language
7. **Professional referral** — always recommends professional help for distress

---

## 🔧 Demo Mode

If IBM API credentials are not configured, the app runs in **Demo Mode** with pre-built responses that still follow all safety guidelines. This is ideal for testing the UI.

---

## 📋 Requirements

- Python 3.10+
- IBM Cloud account (free tier available)
- IBM Watsonx.ai project
- Modern web browser

---

## 🤝 Contributing

Pull requests are welcome! Please ensure any contributions follow the ethical AI principles above and maintain the safety-first approach.

---

## 📄 License

MIT License — see [LICENSE](LICENSE) for details.

---

<div align="center">
Made with 💙 for mental health awareness | Powered by IBM Watsonx.ai & IBM Granite
</div>
