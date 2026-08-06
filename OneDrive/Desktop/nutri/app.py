# encoding: utf-8
"""
MindfulAI — AI-Powered Mental Health Awareness & Suicide Prevention Agent
Backend : Python Flask
AI      : IBM Watsonx.ai (IBM Granite)
Author  : MindfulAI Team
"""

import os
import json
import random
import logging
from datetime import datetime, date, timedelta
from pathlib import Path
from flask import Flask, render_template, request, jsonify, session
from dotenv import load_dotenv

# ─────────────────────────────────────────────────────────────────────────────
#  Load environment variables
# ─────────────────────────────────────────────────────────────────────────────
load_dotenv()

# ─────────────────────────────────────────────────────────────────────────────
#  Load mental-health resource dataset
# ─────────────────────────────────────────────────────────────────────────────
_DATA_PATH = Path(__file__).parent / "data" / "mental_health_resources.json"
with open(_DATA_PATH, "r", encoding="utf-8") as _f:
    RESOURCES: dict = json.load(_f)


# ==============================================================================
#  AGENT INSTRUCTIONS — CUSTOMISE ME!
#  Edit any field below to tailor the agent's personality, tone, safety rules,
#  crisis response behaviour, language, and wellness strategy.
# ==============================================================================
AGENT_INSTRUCTIONS = {

    # ──────────────────────────────────────────────────────────────────────────
    # 1. IDENTITY & PERSONA
    #    Define who the agent is and how it presents itself to users.
    # ──────────────────────────────────────────────────────────────────────────
    "identity": {
        "name": "MindfulAI",
        "role": "Compassionate AI Mental Health Support Companion",
        "avatar_emoji": "🧠",
        # Tone: warm | calm | empathetic | supportive | gentle | professional
        "tone": "warm, calm, deeply empathetic, and gently encouraging",
        # Language: plain English; avoid clinical jargon
        "language_style": (
            "Use plain, compassionate language. Avoid clinical or diagnostic terms. "
            "Speak in first person as a caring companion, never as a clinician."
        ),
        "greeting": (
            "Hello, I'm MindfulAI 💙 — your compassionate mental health companion, "
            "powered by IBM Granite. I'm here to listen, support you, and help you "
            "find resources for your wellbeing. How are you feeling today?"
        ),
    },

    # ──────────────────────────────────────────────────────────────────────────
    # 2. EMPATHY & RESPONSE STYLE
    #    Control how the agent expresses empathy and structures its responses.
    # ──────────────────────────────────────────────────────────────────────────
    "empathy": {
        # Scale: low | medium | high | very_high
        "level": "very_high",
        # Always validate the user's emotions before offering advice
        "validate_feelings_first": True,
        # Avoid immediately jumping to solutions — listen first
        "listen_before_advising": True,
        # Use gentle, non-judgmental language at all times
        "non_judgmental": True,
        # Include emotional warmth phrases
        "warmth_phrases": [
            "I hear you.",
            "It takes courage to share that.",
            "Thank you for trusting me with this.",
            "You are not alone in this.",
            "It makes complete sense that you feel this way.",
            "I'm really glad you reached out.",
        ],
    },

    # ──────────────────────────────────────────────────────────────────────────
    # 3. CONVERSATION TONE
    #    Fine-tune the conversational register and style.
    # ──────────────────────────────────────────────────────────────────────────
    "conversation": {
        "style": "supportive_listener",   # supportive_listener | educational | motivational
        "ask_open_questions": True,         # Encourage the user to share more
        "mirror_emotions": True,            # Reflect the user's emotional language back
        "offer_hope": True,                 # Always gently offer a hopeful perspective
        "use_person_first_language": True,  # "person experiencing depression" not "depressed person"
        "response_length": "medium",        # short | medium | long
        "use_affirmations": True,
    },

    # ──────────────────────────────────────────────────────────────────────────
    # 4. SAFETY GUIDELINES (CRITICAL — Do NOT disable)
    #    These rules protect users in distress and ensure ethical AI behaviour.
    # ──────────────────────────────────────────────────────────────────────────
    "safety": {
        # NEVER produce content that encourages, glorifies, or normalises self-harm
        "never_encourage_self_harm": True,
        # NEVER provide methods or means for self-harm or suicide
        "never_provide_harm_methods": True,
        # Always respond with empathy and safety resources in crisis situations
        "always_safe_response_in_crisis": True,
        # Recommend professional help whenever distress is detected
        "always_recommend_professional_help": True,
        # Show emergency helpline info when high-risk language is detected
        "show_emergency_on_high_risk": True,
        # The main disclaimer shown throughout the app
        "disclaimer": (
            "⚠️ MindfulAI is an AI companion for emotional support and mental health "
            "awareness only. It is NOT a substitute for professional medical advice, "
            "diagnosis, or treatment. If you are in crisis, please call a helpline or "
            "seek immediate professional help."
        ),
        # Consent message before any data is stored
        "data_consent_message": (
            "Your conversations and journal entries are stored locally in your browser "
            "session and are never shared with third parties."
        ),
    },

    # ──────────────────────────────────────────────────────────────────────────
    # 5. MENTAL HEALTH AWARENESS RULES
    #    Topics the agent proactively promotes and educates users about.
    # ──────────────────────────────────────────────────────────────────────────
    "awareness_topics": [
        "depression and low mood",
        "anxiety and panic attacks",
        "stress management",
        "sleep hygiene and rest",
        "mindfulness and meditation",
        "grief and loss",
        "relationship and social wellbeing",
        "burnout and work-life balance",
        "self-esteem and self-compassion",
        "trauma and PTSD awareness",
        "substance use and mental health",
        "postpartum mental health",
        "teenage and adolescent mental health",
        "elderly loneliness and mental health",
    ],

    # ──────────────────────────────────────────────────────────────────────────
    # 6. RISK CLASSIFICATION
    #    Define how the agent classifies user distress and how it responds.
    # ──────────────────────────────────────────────────────────────────────────
    "risk_classification": {
        "low": {
            "label": "Low Risk",
            "color": "#22c55e",
            "action": "Provide empathetic support, self-care tips, and wellness resources.",
        },
        "moderate": {
            "label": "Moderate Risk",
            "color": "#f59e0b",
            "action": (
                "Express strong empathy, recommend grounding techniques, suggest "
                "reaching out to a counselor or trusted person."
            ),
        },
        "high": {
            "label": "High Risk",
            "color": "#ef4444",
            "action": (
                "Respond with maximum empathy and urgency. Immediately display crisis "
                "helpline numbers. Strongly encourage the user to call a helpline or "
                "go to an emergency room. Never leave a high-risk user without resources."
            ),
        },
    },

    # ──────────────────────────────────────────────────────────────────────────
    # 7. CRISIS RESPONSE BEHAVIOUR
    #    How the agent handles immediate crisis situations.
    # ──────────────────────────────────────────────────────────────────────────
    "crisis_response": {
        "immediate_acknowledgement": True,   # Acknowledge the pain immediately
        "provide_helpline_numbers": True,     # Always show helplines in crisis
        "suggest_trusted_person": True,       # Suggest calling a trusted person
        "recommend_emergency_services": True, # Recommend emergency services if needed
        # Do NOT engage in extensive conversation — keep crisis response brief & focused
        "brief_and_focused": True,
        # High-risk trigger phrases (also loaded from dataset for full list)
        "trigger_phrases": [
            "want to die", "kill myself", "end my life", "suicide",
            "no reason to live", "better off dead",
        ],
    },

    # ──────────────────────────────────────────────────────────────────────────
    # 8. SUPPORTED LANGUAGES
    #    The agent responds in the user's detected language.
    # ──────────────────────────────────────────────────────────────────────────
    "supported_languages": ["English", "Hindi", "Spanish", "French", "German"],
    "default_language": "English",
    "auto_detect_language": True,

    # ──────────────────────────────────────────────────────────────────────────
    # 9. WELLNESS RECOMMENDATIONS
    #    Categories of self-care the agent promotes and recommends.
    # ──────────────────────────────────────────────────────────────────────────
    "wellness_recommendations": {
        "mindfulness": True,
        "breathing_exercises": True,
        "journaling": True,
        "physical_activity": True,
        "sleep_hygiene": True,
        "social_connection": True,
        "professional_therapy": True,
        "positive_affirmations": True,
        "creative_expression": True,
        "nutrition_and_hydration": True,
    },

    # ──────────────────────────────────────────────────────────────────────────
    # 10. SYSTEM PROMPT TEMPLATE
    #     Injected as the system message for every IBM Granite API call.
    #     Placeholders are filled at runtime by build_system_prompt().
    # ──────────────────────────────────────────────────────────────────────────
    "system_prompt_template": """You are {name}, a {role}.

TONE & COMMUNICATION STYLE:
- Be {tone}.
- {language_style}
- Always validate the user's feelings before offering advice or resources.
- Use gentle, non-judgmental, compassionate language at all times.
- Speak as a warm, caring companion — never as a clinician or doctor.

CORE RESPONSIBILITIES:
1. Provide empathetic, supportive conversations to people experiencing emotional distress.
2. Promote mental health awareness by sharing educational information and facts.
3. Detect emotional distress signals in the user's words and respond appropriately.
4. Recommend personalised self-care activities: mindfulness, breathing, journaling, sleep tips.
5. Generate daily positive affirmations and wellness tips to support recovery.
6. Maintain a warm, safe conversational space free of judgment.
7. When high-risk language is detected, immediately show empathy and crisis resources.
8. Always recommend professional mental health support when distress is present.

SAFETY RULES (NON-NEGOTIABLE):
- {disclaimer}
- NEVER suggest, provide, or describe methods of self-harm or suicide.
- NEVER tell a user their problems are trivial or invalid.
- NEVER respond with dismissiveness, impatience, or judgment.
- ALWAYS encourage the user to seek professional help when they are struggling.
- If crisis language is detected: respond with empathy first, then immediately provide helpline numbers.

RESPONSE FORMAT:
- Start with an empathetic acknowledgement of what the user said.
- Use warm, caring language throughout.
- Offer 1–2 practical, actionable self-care suggestions when appropriate.
- End with an open, caring question or gentle encouragement.
- Keep responses concise but warm. Do not overwhelm the user with information.
- Use line breaks and simple formatting for readability.
""",
}


# ─────────────────────────────────────────────────────────────────────────────
#  Flask App Setup
# ─────────────────────────────────────────────────────────────────────────────
app = Flask(__name__)
app.secret_key = os.getenv("FLASK_SECRET_KEY", "dev-secret-change-in-production")

logging.basicConfig(level=logging.INFO, format="%(asctime)s %(levelname)s %(message)s")
logger = logging.getLogger(__name__)


# ─────────────────────────────────────────────────────────────────────────────
#  IBM Watsonx.ai Client — lazy initialisation
# ─────────────────────────────────────────────────────────────────────────────
_watsonx_client = None


def get_watsonx_client():
    """Return a cached Watsonx ModelInference client, creating it on first call."""
    global _watsonx_client
    if _watsonx_client is not None:
        return _watsonx_client

    api_key    = os.getenv("IBM_API_KEY", "")
    project_id = os.getenv("WATSONX_PROJECT_ID", "")
    url        = os.getenv("WATSONX_URL", "https://us-south.ml.cloud.ibm.com")
    model_id   = os.getenv("GRANITE_MODEL_ID", "ibm/granite-3-3-8b-instruct")

    if not api_key or api_key == "your_ibm_api_key_here":
        logger.warning("IBM_API_KEY not set — running in demo/mock mode.")
        return None
    if not project_id or project_id == "your_watsonx_project_id_here":
        logger.warning("WATSONX_PROJECT_ID not set — running in demo/mock mode.")
        return None

    try:
        from ibm_watsonx_ai import APIClient, Credentials
        from ibm_watsonx_ai.foundation_models import ModelInference
        from ibm_watsonx_ai.metanames import GenTextParamsMetaNames as GenParams

        credentials = Credentials(url=url, api_key=api_key)
        client      = APIClient(credentials)

        _watsonx_client = ModelInference(
            model_id=model_id,
            api_client=client,
            project_id=project_id,
            params={
                GenParams.MAX_NEW_TOKENS:      1024,
                GenParams.TEMPERATURE:         0.65,
                GenParams.TOP_P:               0.9,
                GenParams.REPETITION_PENALTY:  1.1,
            },
        )
        logger.info("Watsonx.ai client initialised  model=%s", model_id)
        return _watsonx_client

    except ImportError:
        logger.error("ibm-watsonx-ai not installed. Run: pip install ibm-watsonx-ai")
        return None
    except Exception as exc:
        logger.error("Failed to initialise Watsonx client: %s", exc)
        return None


# ─────────────────────────────────────────────────────────────────────────────
#  Build system prompt from AGENT_INSTRUCTIONS
# ─────────────────────────────────────────────────────────────────────────────
def build_system_prompt() -> str:
    ai = AGENT_INSTRUCTIONS
    template = ai["system_prompt_template"]
    return template.format(
        name=ai["identity"]["name"],
        role=ai["identity"]["role"],
        tone=ai["identity"]["tone"],
        language_style=ai["identity"]["language_style"],
        disclaimer=ai["safety"]["disclaimer"],
    )


# ─────────────────────────────────────────────────────────────────────────────
#  RAG Pipeline — retrieve relevant resources to augment the prompt
# ─────────────────────────────────────────────────────────────────────────────
def rag_retrieve(user_message: str, risk_level: str) -> str:
    """
    Retrieval-Augmented Generation pipeline.
    Retrieves relevant mental health resources from the dataset and
    returns them as a formatted context block for the LLM prompt.
    """
    msg_lower = user_message.lower()
    context_parts = []

    # Select self-care activities based on risk level
    activities = RESOURCES["self_care_activities"].get(risk_level, [])
    if activities:
        selected = random.sample(activities, min(3, len(activities)))
        context_parts.append(
            "RELEVANT SELF-CARE SUGGESTIONS:\n" +
            "\n".join(f"- {a}" for a in selected)
        )

    # Inject breathing technique if anxiety/panic/stress is mentioned
    breathing_keywords = ["anxious", "anxiety", "panic", "stress", "breath", "breathe", "overwhelm"]
    if any(k in msg_lower for k in breathing_keywords):
        tech = random.choice(RESOURCES["breathing_techniques"])
        context_parts.append(
            f"BREATHING TECHNIQUE TO RECOMMEND:\n"
            f"Name: {tech['name']}\n"
            f"How: {tech['description']}\n"
            f"Best for: {tech['best_for']}"
        )

    # Inject mindfulness exercise if relevant
    mindfulness_keywords = ["mind", "focus", "ground", "present", "meditat", "relax"]
    if any(k in msg_lower for k in mindfulness_keywords):
        ex = random.choice(RESOURCES["mindfulness_exercises"])
        context_parts.append(
            f"MINDFULNESS EXERCISE TO SUGGEST:\n"
            f"Name: {ex['name']}\n"
            f"How: {ex['description']}\n"
            f"Duration: {ex['duration']}"
        )

    # Inject sleep tip if sleep is mentioned
    sleep_keywords = ["sleep", "insomnia", "awake", "night", "tired", "rest", "exhausted"]
    if any(k in msg_lower for k in sleep_keywords):
        tip = random.choice(RESOURCES["sleep_improvement_tips"])
        context_parts.append(f"SLEEP TIP TO SHARE:\n- {tip}")

    # Inject mental health fact for educational conversations
    context_parts.append(
        "MENTAL HEALTH FACT (share if appropriate):\n"
        f"- {random.choice(RESOURCES['mental_health_facts'])}"
    )

    # Always include an affirmation
    context_parts.append(
        "POSITIVE AFFIRMATION TO SHARE:\n"
        f'"{random.choice(RESOURCES["positive_affirmations"])}"'
    )

    # For high-risk: inject emergency helplines
    if risk_level == "high":
        helplines = RESOURCES["emergency_helplines"][:4]
        lines = "\n".join(
            f"- {h['name']}: {h['number']} ({h['available']})" for h in helplines
        )
        context_parts.append(
            f"EMERGENCY HELPLINES (MUST INCLUDE IN RESPONSE):\n{lines}"
        )

    return "\n\n".join(context_parts)


# ─────────────────────────────────────────────────────────────────────────────
#  Risk Classification — keyword-based pre-screening (RAG stage 1)
# ─────────────────────────────────────────────────────────────────────────────
def classify_risk(text: str) -> str:
    """
    Classify the emotional risk level of the user's message.
    Returns: 'low' | 'moderate' | 'high'
    """
    text_lower = text.lower()
    keywords   = RESOURCES.get("risk_keywords", {})

    for kw in keywords.get("high", []):
        if kw in text_lower:
            return "high"
    for kw in keywords.get("moderate", []):
        if kw in text_lower:
            return "moderate"
    return "low"


# ─────────────────────────────────────────────────────────────────────────────
#  Agent Workflow — main inference pipeline
# ─────────────────────────────────────────────────────────────────────────────
def run_agent(user_message: str, conversation_history: list,
              journal_context: str = "") -> dict:
    """
    Full MindfulAI agent workflow:
    1. Risk classification
    2. RAG retrieval
    3. Prompt construction
    4. IBM Granite inference (or mock fallback)
    5. Return structured response
    """
    # Step 1 — Risk Classification
    risk_level = classify_risk(user_message)
    risk_info  = AGENT_INSTRUCTIONS["risk_classification"][risk_level]

    # Step 2 — RAG retrieval
    rag_context = rag_retrieve(user_message, risk_level)

    # Step 3 — Build augmented prompt
    system_prompt = build_system_prompt()
    if rag_context:
        system_prompt = system_prompt + f"\n\nCONTEXTUAL RESOURCES (use these in your response):\n{rag_context}"

    if journal_context:
        system_prompt += f"\n\nUSER'S RECENT JOURNAL CONTEXT:\n{journal_context}"

    prompt_parts = [f"<|system|>\n{system_prompt}\n"]
    for turn in conversation_history[-8:]:          # keep last 8 turns for context
        role    = turn.get("role", "user")
        content = turn.get("content", "")
        prompt_parts.append(f"<|{role}|>\n{content}")
    prompt_parts.append(f"<|user|>\n{user_message}\n<|assistant|>")
    full_prompt = "\n".join(prompt_parts)

    # Step 4 — Inference
    client = get_watsonx_client()
    if client is not None:
        try:
            response_text = client.generate_text(prompt=full_prompt)
            if not isinstance(response_text, str):
                response_text = str(response_text)
        except Exception as exc:
            logger.error("Watsonx generation error: %s", exc)
            response_text = _mock_response(user_message, risk_level)
    else:
        response_text = _mock_response(user_message, risk_level)

    # Step 5 — Compose structured return
    return {
        "response":   response_text.strip(),
        "risk_level": risk_level,
        "risk_label": risk_info["label"],
        "risk_color": risk_info["color"],
        "timestamp":  datetime.now().isoformat(),
        "model":      os.getenv("GRANITE_MODEL_ID", "ibm/granite-3-3-8b-instruct"),
        "show_emergency": (risk_level == "high"),
    }


def _mock_response(message: str, risk_level: str) -> str:
    """
    Return a canned demo response when IBM credentials are not configured.
    Provides appropriate responses for different risk levels.
    """
    msg = message.lower()
    ai  = AGENT_INSTRUCTIONS

    # High-risk demo response
    if risk_level == "high":
        return (
            "💙 I can hear that you're going through something incredibly painful right now, "
            "and I want you to know — your life has value, and you are not alone in this.\n\n"
            "**Please reach out for immediate support:**\n"
            "- 📞 **iCall (India):** 9152987821 (Mon–Sat, 8am–10pm)\n"
            "- 📞 **Vandrevala Foundation:** 1860-2662-345 (24/7)\n"
            "- 📞 **988 Suicide Lifeline (USA):** 988 (24/7)\n"
            "- 💬 **Crisis Text Line:** Text HOME to 741741\n\n"
            "Please call one of these numbers now, or ask someone near you to be with you. "
            "You deserve support from a caring professional right now. 💙\n\n"
            "*[Demo Mode — connect IBM Watsonx.ai for full AI support]*"
        )

    # Moderate-risk demo response
    if risk_level == "moderate":
        return (
            "💙 Thank you for sharing what you're going through — it takes real courage "
            "to open up, and I hear you. What you're feeling is completely valid.\n\n"
            "**A gentle grounding exercise for right now:**\n"
            "Try the 5-4-3-2-1 technique: Name **5 things you can see**, 4 you can touch, "
            "3 you can hear, 2 you can smell, and 1 you can taste. "
            "This helps bring your mind back to the present moment.\n\n"
            "When you feel ready, it would really help to talk to a counselor or someone "
            "you trust. Would you like some tips for finding support? 💙\n\n"
            "*[Demo Mode — connect IBM Watsonx.ai for personalised AI responses]*"
        )

    # Greetings
    if any(k in msg for k in ["hello", "hi", "hey", "start", "good morning", "good evening"]):
        return ai["identity"]["greeting"]

    # Mood / wellbeing
    if any(k in msg for k in ["sad", "depressed", "lonely", "alone", "empty", "numb"]):
        return (
            "💙 I hear you, and I'm really glad you reached out. Feeling sad or empty "
            "can be really heavy, and it's okay to acknowledge that.\n\n"
            "You don't have to face this alone. Here's one small thing you could try:\n"
            "✨ **Breathing exercise:** Breathe in slowly for 4 counts, hold for 4, "
            "breathe out for 4, hold for 4. Repeat 3–4 times.\n\n"
            "\"You have survived every difficult day so far — that is remarkable strength.\"\n\n"
            "Is there something specific on your mind you'd like to talk about? 💙\n\n"
            "*[Demo Mode — connect IBM Watsonx.ai for full AI support]*"
        )

    if any(k in msg for k in ["stress", "anxious", "anxiety", "panic", "worried", "overwhelm"]):
        return (
            "💙 Feeling anxious or overwhelmed is exhausting, and I want you to know "
            "that what you're experiencing is real and valid.\n\n"
            "**Box Breathing — try this right now:**\n"
            "Inhale for 4 counts → Hold for 4 → Exhale for 4 → Hold for 4.\n"
            "Repeat 4–6 times. This activates your body's natural calming response.\n\n"
            "One small step at a time — you don't have to solve everything today. "
            "What's feeling most overwhelming right now? 💙\n\n"
            "*[Demo Mode — connect IBM Watsonx.ai for full AI support]*"
        )

    if any(k in msg for k in ["sleep", "insomnia", "awake", "tired", "exhausted"]):
        return (
            "💙 Sleep struggles can make everything feel harder. You're not alone in this.\n\n"
            "**Tonight, try this:**\n"
            "- Dim your lights 30 minutes before bed 🌙\n"
            "- Write down any worries in a journal to 'release' them before sleeping\n"
            "- Try 4-7-8 breathing: inhale 4 counts, hold 7, exhale 8\n\n"
            "Your rest matters — your mind and body need it to heal. 💙\n\n"
            "*[Demo Mode — connect IBM Watsonx.ai for full AI support]*"
        )

    # Default low-risk response
    affirmation = random.choice(RESOURCES["positive_affirmations"])
    wellness    = random.choice(RESOURCES["wellness_tips"])
    return (
        f"💙 Thank you for sharing with me today. I'm here to listen and support you.\n\n"
        f"**Today's affirmation for you:**\n✨ *\"{affirmation}\"*\n\n"
        f"**A gentle wellness tip:**\n🌱 {wellness}\n\n"
        f"How are you feeling right now? I'd love to hear more about what's on your mind. 💙\n\n"
        "*[Demo Mode — add IBM API credentials in .env for full AI support]*"
    )


# ─────────────────────────────────────────────────────────────────────────────
#  Mood / Wellness Score Utilities
# ─────────────────────────────────────────────────────────────────────────────
MOOD_SCORES = {
    "😄 Great":     5,
    "🙂 Good":      4,
    "😐 Neutral":   3,
    "😔 Low":       2,
    "😢 Struggling": 1,
}

def calc_wellness_score(mood_history: list) -> int:
    """
    Calculate a 0–100 wellness score from the last 7 mood entries.
    Higher mood scores → higher wellness score.
    """
    if not mood_history:
        return 50
    recent = mood_history[-7:]
    avg = sum(MOOD_SCORES.get(e.get("mood", "😐 Neutral"), 3) for e in recent) / len(recent)
    return round((avg / 5) * 100)


def calc_stress_level(mood_history: list) -> str:
    """Return Low / Moderate / High stress based on recent mood history."""
    score = calc_wellness_score(mood_history)
    if score >= 70:
        return "Low"
    if score >= 40:
        return "Moderate"
    return "High"


def calc_positive_streak(mood_history: list) -> int:
    """Count consecutive days with a mood score ≥ 4 (Good or Great)."""
    streak = 0
    for entry in reversed(mood_history):
        if MOOD_SCORES.get(entry.get("mood", ""), 0) >= 4:
            streak += 1
        else:
            break
    return streak


# ─────────────────────────────────────────────────────────────────────────────
#  Flask Routes
# ─────────────────────────────────────────────────────────────────────────────

@app.route("/")
def index():
    """Serve the main SPA."""
    return render_template(
        "index.html",
        agent_name    = AGENT_INSTRUCTIONS["identity"]["name"],
        agent_emoji   = AGENT_INSTRUCTIONS["identity"]["avatar_emoji"],
        greeting      = AGENT_INSTRUCTIONS["identity"]["greeting"],
        disclaimer    = AGENT_INSTRUCTIONS["safety"]["disclaimer"],
    )


@app.route("/api/chat", methods=["POST"])
def chat():
    """
    Handle a chat message.
    Runs the full agent workflow: risk classification → RAG → Granite inference.
    """
    data          = request.get_json(force=True)
    user_message  = (data.get("message") or "").strip()
    history       = data.get("history", [])
    journal_ctx   = data.get("journal_context", "")

    if not user_message:
        return jsonify({"error": "Message cannot be empty"}), 400

    result = run_agent(user_message, history, journal_ctx)
    return jsonify(result)


@app.route("/api/mood", methods=["POST"])
def log_mood():
    """Log a mood entry and return updated analytics."""
    data  = request.get_json(force=True)
    mood  = data.get("mood", "😐 Neutral")
    note  = data.get("note", "")
    today = date.today().isoformat()

    # Persist mood history in session (in-memory; front-end also mirrors in localStorage)
    history = session.get("mood_history", [])
    history.append({
        "date":  today,
        "mood":  mood,
        "score": MOOD_SCORES.get(mood, 3),
        "note":  note,
    })
    session["mood_history"] = history[-90:]  # keep last 90 days

    # Build weekly trend data (last 7 days)
    today_dt = date.today()
    weekly   = []
    for i in range(6, -1, -1):
        d   = (today_dt - timedelta(days=i)).isoformat()
        day_entries = [e for e in history if e["date"] == d]
        avg_score   = (
            sum(e["score"] for e in day_entries) / len(day_entries)
            if day_entries else None
        )
        weekly.append({
            "date":  d,
            "score": round(avg_score, 1) if avg_score is not None else None,
            "label": (today_dt - timedelta(days=i)).strftime("%a"),
        })

    return jsonify({
        "logged":          True,
        "wellness_score":  calc_wellness_score(history),
        "stress_level":    calc_stress_level(history),
        "positive_streak": calc_positive_streak(history),
        "weekly_trend":    weekly,
        "total_entries":   len(history),
    })


@app.route("/api/mood/history", methods=["GET"])
def get_mood_history():
    """Return full mood history from session."""
    history = session.get("mood_history", [])
    return jsonify({
        "history":         history,
        "wellness_score":  calc_wellness_score(history),
        "stress_level":    calc_stress_level(history),
        "positive_streak": calc_positive_streak(history),
    })


@app.route("/api/journal", methods=["POST"])
def save_journal():
    """
    Save a journal entry and analyse emotional content.
    Uses risk classification to provide insights.
    """
    data    = request.get_json(force=True)
    content = (data.get("content") or "").strip()
    mood    = data.get("mood", "😐 Neutral")
    title   = data.get("title", "Journal Entry")

    if not content:
        return jsonify({"error": "Journal content cannot be empty"}), 400

    risk_level = classify_risk(content)
    risk_info  = AGENT_INSTRUCTIONS["risk_classification"][risk_level]

    # AI insight for the journal entry
    prompt = (
        f"The user has written the following journal entry:\n\n\"{content}\"\n\n"
        "Please provide a short (2–3 sentences) empathetic insight about what they may "
        "be experiencing and one gentle, practical suggestion for their wellbeing. "
        "Be warm, non-judgmental, and supportive."
    )
    agent_result = run_agent(prompt, [], journal_context=content)

    # Save to session
    journals = session.get("journals", [])
    entry = {
        "id":         len(journals) + 1,
        "title":      title,
        "content":    content,
        "mood":       mood,
        "risk_level": risk_level,
        "risk_label": risk_info["label"],
        "insight":    agent_result["response"],
        "date":       datetime.now().isoformat(),
    }
    journals.append(entry)
    session["journals"] = journals[-50:]  # keep last 50 entries

    return jsonify({
        "saved":       True,
        "entry":       entry,
        "show_emergency": (risk_level == "high"),
    })


@app.route("/api/journal/history", methods=["GET"])
def get_journal_history():
    """Return all saved journal entries."""
    journals = session.get("journals", [])
    return jsonify({"journals": list(reversed(journals))})


@app.route("/api/affirmation", methods=["GET"])
def get_affirmation():
    """Return today's random positive affirmation and wellness tip."""
    return jsonify({
        "affirmation": random.choice(RESOURCES["positive_affirmations"]),
        "wellness_tip": random.choice(RESOURCES["wellness_tips"]),
        "date": date.today().isoformat(),
    })


@app.route("/api/resources", methods=["GET"])
def get_resources():
    """Return self-care resources, helplines, breathing techniques, and mindfulness exercises."""
    return jsonify({
        "emergency_helplines":  RESOURCES["emergency_helplines"],
        "breathing_techniques": RESOURCES["breathing_techniques"],
        "mindfulness_exercises": RESOURCES["mindfulness_exercises"],
        "sleep_tips":           RESOURCES["sleep_improvement_tips"],
        "mental_health_facts":  RESOURCES["mental_health_facts"],
        "self_care":            RESOURCES["self_care_activities"],
    })


@app.route("/api/dashboard", methods=["GET"])
def get_dashboard():
    """Return all dashboard metrics in one call."""
    history  = session.get("mood_history", [])
    journals = session.get("journals", [])

    # Weekly trend
    today_dt = date.today()
    weekly   = []
    for i in range(6, -1, -1):
        d   = (today_dt - timedelta(days=i)).isoformat()
        day_entries = [e for e in history if e["date"] == d]
        avg_score   = (
            sum(e["score"] for e in day_entries) / len(day_entries)
            if day_entries else None
        )
        weekly.append({
            "date":  d,
            "score": round(avg_score, 1) if avg_score is not None else None,
            "label": (today_dt - timedelta(days=i)).strftime("%a"),
        })

    return jsonify({
        "wellness_score":   calc_wellness_score(history),
        "stress_level":     calc_stress_level(history),
        "positive_streak":  calc_positive_streak(history),
        "total_mood_logs":  len(history),
        "total_journals":   len(journals),
        "weekly_trend":     weekly,
        "mood_history":     history[-14:],  # last 14 entries for timeline
        "affirmation":      random.choice(RESOURCES["positive_affirmations"]),
        "wellness_tip":     random.choice(RESOURCES["wellness_tips"]),
    })


@app.route("/api/health")
def health_check():
    """Health-check endpoint for deployment monitoring."""
    client_status = "connected" if get_watsonx_client() is not None else "demo_mode"
    return jsonify({
        "status":    "ok",
        "agent":     AGENT_INSTRUCTIONS["identity"]["name"],
        "model":     os.getenv("GRANITE_MODEL_ID", "ibm/granite-3-3-8b-instruct"),
        "watsonx":   client_status,
        "timestamp": datetime.now().isoformat(),
    })


# ─────────────────────────────────────────────────────────────────────────────
#  Entry Point
# ─────────────────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    port  = int(os.getenv("PORT", 5000))
    debug = os.getenv("FLASK_ENV", "development") == "development"
    logger.info("Starting MindfulAI on port %d (debug=%s)", port, debug)
    app.run(host="0.0.0.0", port=port, debug=debug)
