/**
 * MindfulAI — Mental Health Awareness & Suicide Prevention Agent
 * Frontend JavaScript
 * IBM Watsonx.ai + IBM Granite | Flask Backend
 */

"use strict";

// ─────────────────────────────────────────────────────────────────────────────
//  Application State
// ─────────────────────────────────────────────────────────────────────────────
const STATE = {
  theme:           localStorage.getItem("mf_theme") || "light",
  currentTab:      "chat",
  chatHistory:     [],            // [{role, content}]
  msgCount:        0,
  selectedMood:    null,
  selfCareDone:    JSON.parse(localStorage.getItem("mf_selfcare") || "[]"),
  weeklyChart:     null,
  distChart:       null,
  moodWeekChart:   null,
  resourcesLoaded: false,
  helpLinesLoaded: false,
};

// Chart colour palette aligned with CSS variables
const CHART_COLORS = {
  green:  "rgba(30,138,110,",
  blue:   "rgba(59,130,212,",
  purple: "rgba(124,92,216,",
  amber:  "rgba(245,158,11,",
  red:    "rgba(239,68,68,",
  teal:   "rgba(100,181,196,",
};

// ─────────────────────────────────────────────────────────────────────────────
//  Initialisation
// ─────────────────────────────────────────────────────────────────────────────
document.addEventListener("DOMContentLoaded", () => {
  applyTheme(STATE.theme);
  addWelcomeMessage();
  loadThemeToggle();
  loadSelfCareState();
  refreshAffirmation();
  loadTrustedContacts();

  // Restore last tab from session
  const savedTab = sessionStorage.getItem("mf_tab");
  if (savedTab && savedTab !== "chat") {
    switchTab(savedTab);
  }
});

// ─────────────────────────────────────────────────────────────────────────────
//  Navigation
// ─────────────────────────────────────────────────────────────────────────────
function switchTab(tabName) {
  // Hide all sections
  document.querySelectorAll(".tab-section").forEach(el => el.classList.remove("active"));
  document.querySelectorAll(".tab-pill").forEach(el => el.classList.remove("active"));
  document.querySelectorAll(".nav-link").forEach(el => el.classList.remove("active"));

  // Show selected
  const section = document.getElementById(`tab-${tabName}`);
  if (section) section.classList.add("active");

  document.querySelectorAll(`[data-tab="${tabName}"]`).forEach(el => el.classList.add("active"));

  STATE.currentTab = tabName;
  sessionStorage.setItem("mf_tab", tabName);

  // Lazy-load data when switching to specific tabs
  if (tabName === "dashboard") loadDashboard();
  if (tabName === "resources" && !STATE.resourcesLoaded) loadResources();
  if (tabName === "emergency" && !STATE.helpLinesLoaded) loadHelplines();
  if (tabName === "journal") loadJournalHistory();
  if (tabName === "mood") renderMoodChartAndMetrics();
}

function enterApp(tab) {
  document.getElementById("heroSection").style.display = "none";
  document.getElementById("appMain").style.display = "block";
  switchTab(tab);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Theme
// ─────────────────────────────────────────────────────────────────────────────
function loadThemeToggle() {
  const btn = document.getElementById("themeToggle");
  if (btn) btn.addEventListener("click", () => {
    STATE.theme = STATE.theme === "light" ? "dark" : "light";
    localStorage.setItem("mf_theme", STATE.theme);
    applyTheme(STATE.theme);
  });
}

function applyTheme(theme) {
  document.documentElement.setAttribute("data-theme", theme);
  const icon = document.getElementById("themeIcon");
  if (!icon) return;
  if (theme === "dark") {
    icon.className = "fa-solid fa-sun";
  } else {
    icon.className = "fa-solid fa-moon";
  }
  // Re-render charts in new theme colours
  if (STATE.weeklyChart)   STATE.weeklyChart.update();
  if (STATE.distChart)     STATE.distChart.update();
  if (STATE.moodWeekChart) STATE.moodWeekChart.update();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Chat
// ─────────────────────────────────────────────────────────────────────────────
function addWelcomeMessage() {
  const greeting =
    "Hello, I'm MindfulAI 💙 — your compassionate mental health companion, " +
    "powered by IBM Granite. I'm here to listen, support you, and help you " +
    "find resources for your wellbeing. How are you feeling today?";
  addBotMessage(greeting, "low");
}

function handleChatKey(e) {
  if (e.key === "Enter" && !e.shiftKey) {
    e.preventDefault();
    sendMessage();
  }
}

function autoResize(el) {
  el.style.height = "auto";
  el.style.height = Math.min(el.scrollHeight, 120) + "px";
}

async function sendMessage() {
  const input = document.getElementById("chatInput");
  const text  = (input.value || "").trim();
  if (!text) return;

  const sendBtn = document.getElementById("sendBtn");
  sendBtn.disabled = true;
  input.value = "";
  input.style.height = "auto";

  addUserMessage(text);
  STATE.chatHistory.push({ role: "user", content: text });
  STATE.msgCount++;
  setText("sidebarMsgCount", STATE.msgCount);

  // Hide quick prompts after first message
  const qp = document.getElementById("quickPrompts");
  if (qp) qp.style.display = "none";

  const typingId = addTypingIndicator();

  try {
    const res = await fetch("/api/chat", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        message: text,
        history: STATE.chatHistory.slice(-8),
      }),
    });

    removeTypingIndicator(typingId);

    if (!res.ok) {
      addBotMessage("⚠️ Something went wrong. Please try again.", "low");
      return;
    }

    const data = await res.json();

    if (data.error) {
      addBotMessage(`⚠️ ${data.error}`, "low");
      return;
    }

    // Update session insights sidebar
    if (data.risk_level) {
      updateRiskDisplay(data.risk_level, data.risk_label, data.risk_color);
    }

    // Show emergency panel if high risk
    if (data.show_emergency) {
      const ep = document.getElementById("emergencyInline");
      if (ep) ep.classList.remove("d-none");
    }

    addBotMessage(data.response, data.risk_level);

    // Push assistant response to history
    STATE.chatHistory.push({ role: "assistant", content: data.response });

  } catch (err) {
    removeTypingIndicator(typingId);
    addBotMessage(
      "💙 I'm having trouble connecting right now. Please check your connection and try again. " +
      "If you're in crisis, please call a helpline immediately.",
      "low"
    );
  } finally {
    sendBtn.disabled = false;
    input.focus();
  }
}

function sendQuick(text) {
  const input = document.getElementById("chatInput");
  if (input) {
    input.value = text;
    sendMessage();
  }
}

function addUserMessage(text) {
  const msgs = document.getElementById("chatMessages");
  const div  = document.createElement("div");
  div.className = "chat-msg user";
  div.innerHTML = `
    <div>
      <div class="msg-bubble">${escapeHtml(text)}</div>
      <span class="msg-time">${formatTime()}</span>
    </div>
    <div class="msg-avatar user-av"><i class="fa-solid fa-user" style="color:white;font-size:.8rem"></i></div>`;
  msgs.appendChild(div);
  scrollChatToBottom();
}

function addBotMessage(text, riskLevel) {
  const msgs = document.getElementById("chatMessages");
  const div  = document.createElement("div");
  div.className = "chat-msg bot";

  let riskBadge = "";
  if (riskLevel === "high")     riskBadge = `<span class="mood-risk-pill risk-high" style="margin-top:6px;display:inline-block">High Risk</span>`;
  if (riskLevel === "moderate") riskBadge = `<span class="mood-risk-pill risk-moderate" style="margin-top:6px;display:inline-block">Moderate Risk</span>`;

  div.innerHTML = `
    <div class="msg-avatar"><span>🧠</span></div>
    <div>
      <div class="msg-bubble">${renderMarkdown(text)}${riskBadge ? `<div>${riskBadge}</div>` : ""}</div>
      <span class="msg-time">${formatTime()} · IBM Granite</span>
    </div>`;
  msgs.appendChild(div);
  scrollChatToBottom();
}

function addTypingIndicator() {
  const msgs = document.getElementById("chatMessages");
  const id   = `typing-${Date.now()}`;
  const div  = document.createElement("div");
  div.className = "chat-msg bot";
  div.id = id;
  div.innerHTML = `
    <div class="msg-avatar"><span>🧠</span></div>
    <div>
      <div class="msg-bubble">
        <div class="typing-dots">
          <span></span><span></span><span></span>
        </div>
      </div>
    </div>`;
  msgs.appendChild(div);
  scrollChatToBottom();
  return id;
}

function removeTypingIndicator(id) {
  const el = document.getElementById(id);
  if (el) el.remove();
}

function scrollChatToBottom() {
  const msgs = document.getElementById("chatMessages");
  if (msgs) msgs.scrollTop = msgs.scrollHeight;
}

function clearChat() {
  const msgs = document.getElementById("chatMessages");
  if (msgs) msgs.innerHTML = "";
  STATE.chatHistory = [];
  STATE.msgCount = 0;
  setText("sidebarMsgCount", "0");
  addWelcomeMessage();
  const ep = document.getElementById("emergencyInline");
  if (ep) ep.classList.add("d-none");
  const qp = document.getElementById("quickPrompts");
  if (qp) qp.style.display = "";
  showToast("Chat cleared 💙");
}

function exportChat() {
  const msgs = document.getElementById("chatMessages");
  if (!msgs) return;
  const lines = [];
  msgs.querySelectorAll(".chat-msg").forEach(msg => {
    const isUser = msg.classList.contains("user");
    const bubble = msg.querySelector(".msg-bubble");
    const time   = msg.querySelector(".msg-time");
    if (bubble) {
      lines.push(`[${isUser ? "You" : "MindfulAI"}] ${time ? time.textContent : ""}`);
      lines.push(bubble.innerText.trim());
      lines.push("");
    }
  });
  downloadText("MindfulAI_chat.txt", lines.join("\n"));
}

function updateRiskDisplay(riskLevel, riskLabel, riskColor) {
  const badge   = document.getElementById("chatRiskBadge");
  const sidebar = document.getElementById("sidebarRisk");
  const cls     = `risk-${riskLevel}`;

  if (badge) {
    badge.textContent = riskLabel;
    badge.className   = `risk-badge ${cls}`;
    badge.classList.remove("d-none");
    badge.style.borderColor = riskColor;
  }
  if (sidebar) {
    sidebar.textContent = riskLabel;
    sidebar.className   = `risk-pill ${cls}`;
  }
}

// ─────────────────────────────────────────────────────────────────────────────
//  Mood Tracker
// ─────────────────────────────────────────────────────────────────────────────
function selectMood(btn) {
  document.querySelectorAll(".mood-btn").forEach(b => b.classList.remove("selected"));
  btn.classList.add("selected");
  STATE.selectedMood = btn.dataset.mood;
  document.getElementById("logMoodBtn").disabled = false;
}

async function logMood() {
  if (!STATE.selectedMood) return;
  const note    = (document.getElementById("moodNote")?.value || "").trim();
  const logBtn  = document.getElementById("logMoodBtn");
  logBtn.disabled = true;

  try {
    const res = await fetch("/api/mood", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ mood: STATE.selectedMood, note }),
    });
    const data = await res.json();

    // Show success
    const success = document.getElementById("moodLogSuccess");
    if (success) { success.classList.remove("d-none"); setTimeout(() => success.classList.add("d-none"), 3000); }

    // Update metric displays
    updateMoodMetrics(data);

    // Save to localStorage for persistence
    const history = JSON.parse(localStorage.getItem("mf_mood_history") || "[]");
    history.push({
      date:  new Date().toISOString().split("T")[0],
      mood:  STATE.selectedMood,
      score: getMoodScore(STATE.selectedMood),
      note,
    });
    localStorage.setItem("mf_mood_history", JSON.stringify(history.slice(-90)));

    // Re-render chart
    renderMoodChartAndMetrics();
    updateMoodTimeline();

    // Reset
    document.querySelectorAll(".mood-btn").forEach(b => b.classList.remove("selected"));
    if (document.getElementById("moodNote")) document.getElementById("moodNote").value = "";
    STATE.selectedMood = null;
    logBtn.disabled = true;

    showToast("Mood logged 💙 Keep tracking your wellbeing!");

  } catch (err) {
    showToast("Could not save mood. Please try again.", 4000);
    logBtn.disabled = false;
  }
}

function getMoodScore(mood) {
  const scores = { "😄 Great": 5, "🙂 Good": 4, "😐 Neutral": 3, "😔 Low": 2, "😢 Struggling": 1 };
  return scores[mood] || 3;
}

function updateMoodMetrics(data) {
  if (data.wellness_score !== undefined) {
    setText("dashWellnessScore", data.wellness_score);
    setText("moodWellnessScore", data.wellness_score);
    const bar = document.getElementById("dashWellnessBar");
    if (bar) bar.style.width = data.wellness_score + "%";
  }
  if (data.stress_level) {
    setText("dashStressLevel", data.stress_level);
    setText("moodStressLevel", data.stress_level);
    const indicator = document.getElementById("dashStressIndicator");
    if (indicator) {
      const colors = { Low: "var(--success)", Moderate: "var(--warning)", High: "var(--danger)" };
      indicator.style.background = colors[data.stress_level] || "var(--warning)";
    }
  }
  if (data.positive_streak !== undefined) {
    setText("dashStreak", data.positive_streak);
    setText("moodStreak", data.positive_streak + " 🔥");
  }
  if (data.total_entries !== undefined) {
    setText("dashMoodLogs", data.total_entries);
  }
}

function renderMoodChartAndMetrics() {
  const history = JSON.parse(localStorage.getItem("mf_mood_history") || "[]");

  // Build weekly data (last 7 days)
  const today = new Date();
  const labels = [];
  const scores = [];
  for (let i = 6; i >= 0; i--) {
    const d = new Date(today);
    d.setDate(today.getDate() - i);
    const isoDate = d.toISOString().split("T")[0];
    labels.push(d.toLocaleDateString("en", { weekday: "short" }));
    const dayEntries = history.filter(e => e.date === isoDate);
    if (dayEntries.length) {
      const avg = dayEntries.reduce((s, e) => s + (e.score || 3), 0) / dayEntries.length;
      scores.push(parseFloat(avg.toFixed(1)));
    } else {
      scores.push(null);
    }
  }

  // Weekly chart (Mood tab)
  const moodCtx = document.getElementById("moodWeekChart");
  if (moodCtx) {
    if (STATE.moodWeekChart) STATE.moodWeekChart.destroy();
    STATE.moodWeekChart = new Chart(moodCtx, {
      type: "line",
      data: {
        labels,
        datasets: [{
          label: "Mood Score",
          data: scores,
          borderColor: "rgba(30,138,110,1)",
          backgroundColor: "rgba(30,138,110,0.12)",
          borderWidth: 2.5,
          pointBackgroundColor: "rgba(30,138,110,1)",
          pointRadius: 5,
          pointHoverRadius: 7,
          fill: true,
          tension: 0.4,
          spanGaps: true,
        }],
      },
      options: {
        responsive: true,
        maintainAspectRatio: true,
        plugins: { legend: { display: false } },
        scales: {
          y: {
            min: 1, max: 5,
            ticks: {
              stepSize: 1,
              color: getCSSVar("--text-muted"),
              callback: v => ["", "😢", "😔", "😐", "🙂", "😄"][v] || v,
            },
            grid: { color: getCSSVar("--border") },
          },
          x: {
            ticks: { color: getCSSVar("--text-muted") },
            grid: { display: false },
          },
        },
      },
    });
  }

  // Metrics
  if (history.length) {
    const recent7 = history.slice(-7);
    const avg     = recent7.reduce((s, e) => s + (e.score || 3), 0) / recent7.length;
    const wellness = Math.round((avg / 5) * 100);

    let stress = "Moderate";
    if (wellness >= 70) stress = "Low";
    else if (wellness < 40) stress = "High";

    let streak = 0;
    for (let i = history.length - 1; i >= 0; i--) {
      if ((history[i].score || 0) >= 4) streak++;
      else break;
    }

    setText("moodWellnessScore", wellness);
    setText("moodStressLevel", stress);
    setText("moodStreak", streak + " 🔥");
    setText("dashWellnessScore", wellness);
    setText("dashStressLevel", stress);
    setText("dashStreak", streak);
    setText("dashMoodLogs", history.length);

    const bar = document.getElementById("dashWellnessBar");
    if (bar) bar.style.width = wellness + "%";

    const indicator = document.getElementById("dashStressIndicator");
    if (indicator) {
      const colors = { Low: "var(--success)", Moderate: "var(--warning)", High: "var(--danger)" };
      indicator.style.background = colors[stress] || "var(--warning)";
    }
  }
}

// ─────────────────────────────────────────────────────────────────────────────
//  Dashboard
// ─────────────────────────────────────────────────────────────────────────────
async function loadDashboard() {
  try {
    const res  = await fetch("/api/dashboard");
    const data = await res.json();

    updateMoodMetrics(data);

    if (data.affirmation) {
      setText("affirmationText", data.affirmation);
      setText("sidebarAffirmation", data.affirmation);
    }
    if (data.wellness_tip) {
      setText("wellnessTipText", data.wellness_tip);
    }

    // Render weekly chart
    renderWeeklyChart(data.weekly_trend || []);
    renderMoodDistChart(data.mood_history || []);
    updateMoodTimeline();
    renderMoodChartAndMetrics();

  } catch (err) {
    // Fall back to localStorage data
    renderMoodChartAndMetrics();
    updateMoodTimeline();
  }
}

function renderWeeklyChart(weeklyData) {
  const ctx = document.getElementById("weeklyTrendChart");
  if (!ctx) return;

  const labels = weeklyData.map(d => d.label);
  const scores = weeklyData.map(d => d.score);

  if (STATE.weeklyChart) STATE.weeklyChart.destroy();
  STATE.weeklyChart = new Chart(ctx, {
    type: "line",
    data: {
      labels,
      datasets: [{
        label: "Emotional Wellbeing",
        data: scores,
        borderColor: "rgba(30,138,110,1)",
        backgroundColor: "rgba(30,138,110,0.1)",
        borderWidth: 2.5,
        pointBackgroundColor: scores.map(s =>
          s === null ? "transparent" :
          s >= 4 ? "rgba(34,197,94,1)" :
          s >= 3 ? "rgba(30,138,110,1)" :
          s >= 2 ? "rgba(245,158,11,1)" : "rgba(239,68,68,1)"
        ),
        pointRadius: 6,
        pointHoverRadius: 8,
        fill: true,
        tension: 0.4,
        spanGaps: true,
      }],
    },
    options: {
      responsive: true,
      maintainAspectRatio: false,
      plugins: {
        legend: { display: false },
        tooltip: {
          callbacks: {
            label: ctx => {
              const v = ctx.parsed.y;
              if (v === null) return "No data";
              const emojis = ["", "😢 Struggling", "😔 Low", "😐 Neutral", "🙂 Good", "😄 Great"];
              return emojis[Math.round(v)] || `Score: ${v}`;
            },
          },
        },
      },
      scales: {
        y: {
          min: 1, max: 5,
          ticks: {
            stepSize: 1,
            color: getCSSVar("--text-muted"),
            callback: v => ["", "😢", "😔", "😐", "🙂", "😄"][v] || v,
          },
          grid: { color: getCSSVar("--border") },
        },
        x: {
          ticks: { color: getCSSVar("--text-muted") },
          grid: { display: false },
        },
      },
    },
  });
}

function renderMoodDistChart(moodHistory) {
  const ctx = document.getElementById("moodDistChart");
  if (!ctx) return;

  const counts = { "😄 Great": 0, "🙂 Good": 0, "😐 Neutral": 0, "😔 Low": 0, "😢 Struggling": 0 };

  // Merge server history + localStorage history
  const local = JSON.parse(localStorage.getItem("mf_mood_history") || "[]");
  const all   = [...moodHistory, ...local];
  all.forEach(e => { if (counts[e.mood] !== undefined) counts[e.mood]++; });

  if (STATE.distChart) STATE.distChart.destroy();
  STATE.distChart = new Chart(ctx, {
    type: "doughnut",
    data: {
      labels: Object.keys(counts),
      datasets: [{
        data: Object.values(counts),
        backgroundColor: [
          "rgba(34,197,94,0.75)",
          "rgba(30,138,110,0.75)",
          "rgba(100,181,196,0.75)",
          "rgba(245,158,11,0.75)",
          "rgba(239,68,68,0.75)",
        ],
        borderWidth: 2,
        borderColor: getCSSVar("--card-bg"),
        hoverOffset: 6,
      }],
    },
    options: {
      responsive: true,
      maintainAspectRatio: false,
      cutout: "62%",
      plugins: {
        legend: {
          position: "bottom",
          labels: {
            boxWidth: 12,
            font: { size: 11 },
            color: getCSSVar("--text-muted"),
          },
        },
      },
    },
  });
}

function updateMoodTimeline() {
  const container = document.getElementById("moodTimeline");
  if (!container) return;

  const history = JSON.parse(localStorage.getItem("mf_mood_history") || "[]");
  if (!history.length) return;

  const html = history
    .slice(-10)
    .reverse()
    .map(entry => {
      const emoji  = entry.mood?.split(" ")[0] || "😐";
      const label  = entry.mood || "Neutral";
      const date   = entry.date ? new Date(entry.date).toLocaleDateString("en", { month: "short", day: "numeric" }) : "";
      const note   = entry.note ? `<div class="mood-entry-note">"${escapeHtml(entry.note)}"</div>` : "";
      return `
        <div class="mood-entry">
          <div class="mood-entry-emoji">${emoji}</div>
          <div class="mood-entry-info">
            <div class="mood-entry-mood">${escapeHtml(label)}</div>
            <div class="mood-entry-date">${date}</div>
            ${note}
          </div>
        </div>`;
    })
    .join("");

  container.innerHTML = html;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Affirmation
// ─────────────────────────────────────────────────────────────────────────────
async function refreshAffirmation() {
  try {
    const res  = await fetch("/api/affirmation");
    const data = await res.json();
    if (data.affirmation) {
      setText("affirmationText", data.affirmation);
      setText("sidebarAffirmation", data.affirmation);
    }
    if (data.wellness_tip) setText("wellnessTipText", data.wellness_tip);
  } catch (e) {
    // Silent fail
  }
}

// ─────────────────────────────────────────────────────────────────────────────
//  Journal
// ─────────────────────────────────────────────────────────────────────────────
async function saveJournal() {
  const title   = (document.getElementById("journalTitle")?.value  || "").trim() || "Journal Entry";
  const content = (document.getElementById("journalContent")?.value || "").trim();
  const mood    = document.getElementById("journalMood")?.value || "😐 Neutral";

  if (!content) {
    showToast("Please write something before saving 💙", 3000);
    return;
  }

  const btn = document.getElementById("saveJournalBtn");
  btn.disabled = true;
  btn.innerHTML = `<i class="fa-solid fa-spinner fa-spin me-2"></i>Saving…`;

  try {
    const res  = await fetch("/api/journal", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ title, content, mood }),
    });
    const data = await res.json();

    if (data.entry) {
      // Save to localStorage
      const journals = JSON.parse(localStorage.getItem("mf_journals") || "[]");
      journals.push(data.entry);
      localStorage.setItem("mf_journals", JSON.stringify(journals.slice(-50)));

      // Show insight modal
      showJournalInsight(data.entry);

      // Clear form
      if (document.getElementById("journalTitle"))   document.getElementById("journalTitle").value   = "";
      if (document.getElementById("journalContent")) document.getElementById("journalContent").value = "";

      loadJournalHistory();
      showToast("Journal entry saved 💙");

      if (data.show_emergency) {
        setTimeout(() => {
          showToast("💙 If you're struggling, please reach out for support. Help is available.", 6000);
        }, 2000);
      }
    }

  } catch (err) {
    showToast("Could not save journal entry. Please try again.", 4000);
  } finally {
    btn.disabled = false;
    btn.innerHTML = `<i class="fa-solid fa-floppy-disk me-2"></i>Save &amp; Get AI Insight`;
  }
}

function showJournalInsight(entry) {
  const modal   = document.getElementById("journalInsightModal");
  const content = document.getElementById("journalInsightContent");
  if (!modal || !content) return;

  const riskColor = { low: "#22c55e", moderate: "#f59e0b", high: "#ef4444" }[entry.risk_level] || "#22c55e";

  content.innerHTML = `
    <div class="mb-3 d-flex align-items-center gap-2">
      <span class="fw-semibold">${entry.mood || ""}</span>
      <span class="journal-risk-badge" style="background:${riskColor}22;color:${riskColor};">${entry.risk_label || ""}</span>
    </div>
    <div class="journal-insight-text ai-output">${renderMarkdown(entry.insight || "")}</div>
    ${entry.risk_level === "high" ? `
    <div class="mt-3 p-3" style="background:rgba(239,68,68,.06);border:1px solid rgba(239,68,68,.2);border-radius:9px;">
      <div class="fw-semibold text-danger mb-2"><i class="fa-solid fa-phone me-1"></i>Please reach out for support:</div>
      <div><a href="tel:9152987821" class="text-danger fw-semibold">iCall: 9152987821</a> · <a href="tel:988" class="text-danger fw-semibold">988 (USA)</a></div>
    </div>` : ""}`;

  new bootstrap.Modal(modal).show();
}

function loadJournalHistory() {
  const container = document.getElementById("journalList");
  if (!container) return;

  const journals = JSON.parse(localStorage.getItem("mf_journals") || "[]");
  setText("journalCount", `${journals.length} ${journals.length === 1 ? "entry" : "entries"}`);

  if (!journals.length) {
    container.innerHTML = `
      <div class="text-center text-muted py-5">
        <i class="fa-solid fa-book-open fa-2x mb-2 opacity-50"></i>
        <p class="mb-0">Your journal entries will appear here</p>
        <p class="small mt-1">Writing regularly builds emotional resilience</p>
      </div>`;
    return;
  }

  const html = [...journals]
    .reverse()
    .map(entry => {
      const riskColor = { low: "#22c55e", moderate: "#f59e0b", high: "#ef4444" }[entry.risk_level] || "#22c55e";
      const date      = entry.date ? new Date(entry.date).toLocaleDateString("en", {
        month: "short", day: "numeric", year: "numeric",
      }) : "";
      return `
        <div class="journal-entry" onclick="showJournalInsight(${escapeHtml(JSON.stringify(entry))})">
          <div class="journal-entry-header">
            <div class="journal-entry-title">${escapeHtml(entry.title || "Journal Entry")}</div>
            <span class="journal-risk-badge" style="background:${riskColor}22;color:${riskColor};">${entry.risk_label || ""}</span>
          </div>
          <div class="journal-entry-meta">${entry.mood || ""} · ${date}</div>
          <div class="journal-entry-preview">${escapeHtml(entry.content || "")}</div>
        </div>`;
    })
    .join("");

  container.innerHTML = html;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Self-Care Progress
// ─────────────────────────────────────────────────────────────────────────────
function loadSelfCareState() {
  const today    = new Date().toISOString().split("T")[0];
  const saved    = JSON.parse(localStorage.getItem("mf_selfcare") || "{}");
  const dayData  = saved[today] || [];
  STATE.selfCareDone = dayData;
  updateSelfCareUI(dayData);
}

function toggleSelfCare(btn, activity) {
  const today   = new Date().toISOString().split("T")[0];
  const saved   = JSON.parse(localStorage.getItem("mf_selfcare") || "{}");
  const dayData = saved[today] || [];

  if (dayData.includes(activity)) {
    const idx = dayData.indexOf(activity);
    dayData.splice(idx, 1);
    btn.classList.remove("checked");
  } else {
    dayData.push(activity);
    btn.classList.add("checked");
  }

  saved[today] = dayData;
  localStorage.setItem("mf_selfcare", JSON.stringify(saved));
  STATE.selfCareDone = dayData;
  updateSelfCareUI(dayData);
}

function updateSelfCareUI(dayData) {
  const total = 3;
  const done  = dayData.length;
  setText("selfCareCount", `${done} / ${total} today`);
  const bar = document.getElementById("selfCareBar");
  if (bar) bar.style.width = `${Math.round((done / total) * 100)}%`;

  document.querySelectorAll(".self-care-check").forEach(btn => {
    const act = btn.getAttribute("onclick")?.match(/'([^']+)'\)/)?.[1];
    if (act && dayData.includes(act)) btn.classList.add("checked");
  });
}

// ─────────────────────────────────────────────────────────────────────────────
//  Resources
// ─────────────────────────────────────────────────────────────────────────────
async function loadResources() {
  STATE.resourcesLoaded = true;
  try {
    const res  = await fetch("/api/resources");
    const data = await res.json();

    // Breathing techniques
    const breathingEl = document.getElementById("breathingCards");
    if (breathingEl && data.breathing_techniques) {
      breathingEl.innerHTML = data.breathing_techniques.map(t => `
        <div class="col-md-6 col-lg-4">
          <div class="resource-card">
            <div class="resource-card-icon">🌬️</div>
            <div class="resource-card-title">${escapeHtml(t.name)}</div>
            <div class="resource-card-text">${escapeHtml(t.description)}</div>
            <span class="resource-card-tag">${escapeHtml(t.best_for)}</span>
          </div>
        </div>`).join("");
    }

    // Mindfulness
    const mindfulEl = document.getElementById("mindfulnessCards");
    if (mindfulEl && data.mindfulness_exercises) {
      mindfulEl.innerHTML = data.mindfulness_exercises.map(e => `
        <div class="col-md-6">
          <div class="resource-card">
            <div class="resource-card-icon">🧘</div>
            <div class="resource-card-title">${escapeHtml(e.name)}</div>
            <div class="resource-card-text">${escapeHtml(e.description)}</div>
            <span class="resource-card-tag">${escapeHtml(e.duration)}</span>
          </div>
        </div>`).join("");
    }

    // Sleep tips
    const sleepEl = document.getElementById("sleepCards");
    if (sleepEl && data.sleep_tips) {
      sleepEl.innerHTML = data.sleep_tips.map((tip, i) => `
        <div class="col-md-6 col-lg-4">
          <div class="sleep-tip">
            <div class="sleep-tip-num">${i + 1}</div>
            <div>${escapeHtml(tip)}</div>
          </div>
        </div>`).join("");
    }

    // Facts
    const factsEl = document.getElementById("factsCards");
    if (factsEl && data.mental_health_facts) {
      factsEl.innerHTML = data.mental_health_facts.map(f => `
        <div class="col-md-6">
          <div class="fact-card">
            <i class="fa-solid fa-lightbulb me-2" style="color:var(--accent2)"></i>${escapeHtml(f)}
          </div>
        </div>`).join("");
    }

    // Affirmations
    const affirmEl = document.getElementById("affirmationsGrid");
    if (affirmEl) {
      const all = [
        ...(data.mental_health_facts ? [] : []),
      ];
      // Fetch from affirmation endpoint
      const affRes  = await fetch("/api/affirmation");
      const affData = await affRes.json();
      // Build 15 affirmations
      const AFFIRMATIONS = [
        "You are worthy of love and belonging — exactly as you are.",
        "Every small step forward matters, even when it doesn't feel that way.",
        "It is okay to not be okay. You don't have to have it all together.",
        "You have survived every difficult day so far — that is remarkable strength.",
        "Your feelings are valid. You deserve to be heard.",
        "Healing is not linear. Be gentle with yourself today.",
        "You matter more than you know to the people in your life.",
        "This moment will pass. You have the strength to get through it.",
        "Asking for help is one of the bravest things you can do.",
        "You are doing better than you think.",
        "Your mental health deserves the same care as your physical health.",
        "Today, choose one kind act for yourself — you deserve it.",
        "Even on your hardest days, you are enough.",
        "Progress, not perfection. One moment at a time.",
        "You are not alone in this journey.",
      ];
      affirmEl.innerHTML = AFFIRMATIONS
        .map(a => `<div class="affirmation-card">"${escapeHtml(a)}"</div>`)
        .join("");
    }

  } catch (err) {
    showToast("Could not load resources. Please try again.", 4000);
  }
}

function showResourceTab(tab) {
  document.querySelectorAll(".resource-tab").forEach(b => b.classList.remove("active"));
  document.querySelectorAll(".resource-content").forEach(c => c.classList.remove("active"));

  document.querySelector(`[onclick="showResourceTab('${tab}')"]`)?.classList.add("active");
  const el = document.getElementById(`resource-${tab}`);
  if (el) el.classList.add("active");
}

// ─────────────────────────────────────────────────────────────────────────────
//  Emergency Helplines
// ─────────────────────────────────────────────────────────────────────────────
async function loadHelplines() {
  STATE.helpLinesLoaded = true;
  try {
    const res  = await fetch("/api/resources");
    const data = await res.json();

    const container = document.getElementById("helplineCards");
    if (container && data.emergency_helplines) {
      container.innerHTML = data.emergency_helplines.map(h => `
        <div class="col-md-6 col-lg-4">
          <div class="helpline-card">
            <div class="helpline-region"><i class="fa-solid fa-location-dot me-1"></i>${escapeHtml(h.region)}</div>
            <div class="helpline-name">${escapeHtml(h.name)}</div>
            <div class="helpline-number">${escapeHtml(h.number)}</div>
            <div class="helpline-hours"><i class="fa-regular fa-clock me-1"></i>${escapeHtml(h.available)}</div>
            <a href="tel:${h.number.replace(/[^0-9+]/g,'')}" class="helpline-call">
              <i class="fa-solid fa-phone me-1"></i>Call Now
            </a>
            ${h.website ? `<a href="${escapeHtml(h.website)}" target="_blank" rel="noopener" class="helpline-call ms-2" style="background:rgba(59,130,212,.1);color:var(--accent2);border-color:rgba(59,130,212,.25)"><i class="fa-solid fa-arrow-up-right-from-square me-1"></i>Website</a>` : ""}
          </div>
        </div>`).join("");
    }

  } catch (err) {
    showToast("Could not load helplines. Please try again.", 4000);
  }
}

// ─────────────────────────────────────────────────────────────────────────────
//  Trusted Contacts
// ─────────────────────────────────────────────────────────────────────────────
function saveTrustedContacts() {
  const n1 = document.getElementById("trustedName1")?.value  || "";
  const p1 = document.getElementById("trustedPhone1")?.value || "";
  const n2 = document.getElementById("trustedName2")?.value  || "";
  const p2 = document.getElementById("trustedPhone2")?.value || "";

  localStorage.setItem("mf_trusted", JSON.stringify([
    { name: n1, phone: p1 },
    { name: n2, phone: p2 },
  ]));

  const saved = document.getElementById("trustedSaved");
  if (saved) { saved.classList.remove("d-none"); setTimeout(() => saved.classList.add("d-none"), 3000); }
  showToast("Trusted contacts saved 💙");
}

function loadTrustedContacts() {
  try {
    const contacts = JSON.parse(localStorage.getItem("mf_trusted") || "[]");
    if (contacts[0]) {
      setValue("trustedName1",  contacts[0].name);
      setValue("trustedPhone1", contacts[0].phone);
    }
    if (contacts[1]) {
      setValue("trustedName2",  contacts[1].name);
      setValue("trustedPhone2", contacts[1].phone);
    }
  } catch (_) {}
}

// ─────────────────────────────────────────────────────────────────────────────
//  Utility Functions
// ─────────────────────────────────────────────────────────────────────────────
function showLoading(text = "MindfulAI is thinking…") {
  const overlay = document.getElementById("loadingOverlay");
  if (overlay) overlay.classList.remove("d-none");
  setText("loadingText", text);
}

function hideLoading() {
  const overlay = document.getElementById("loadingOverlay");
  if (overlay) overlay.classList.add("d-none");
}

function showToast(message, duration = 3500) {
  const toastEl = document.getElementById("statusToast");
  const msgEl   = document.getElementById("toastMsg");
  if (!toastEl || !msgEl) return;
  msgEl.textContent = message;
  const toast = new bootstrap.Toast(toastEl, { delay: duration, autohide: true });
  toast.show();
}

function renderMarkdown(text) {
  if (!text) return "";
  return text
    .replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;")  // escape HTML first
    .replace(/\*\*(.+?)\*\*/g, "<strong>$1</strong>")  // bold
    .replace(/\*(.+?)\*/g, "<em>$1</em>")              // italic
    .replace(/^### (.+)$/gm, "<h3>$1</h3>")
    .replace(/^## (.+)$/gm,  "<h2>$1</h2>")
    .replace(/^# (.+)$/gm,   "<h1>$1</h1>")
    .replace(/^- (.+)$/gm,   "<li>$1</li>")
    .replace(/^\d+\. (.+)$/gm,"<li>$1</li>")
    .replace(/(<li>[\s\S]*?<\/li>)/g, "<ul>$1</ul>")   // wrap lists (approx.)
    .replace(/<\/ul><ul>/g, "")                         // merge adjacent lists
    .replace(/`([^`]+)`/g,   "<code>$1</code>")
    .replace(/\n{2,}/g, "<br><br>")
    .replace(/\n/g,   "<br>");
}

function escapeHtml(text) {
  if (typeof text !== "string") return String(text ?? "");
  return text
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;")
    .replace(/"/g, "&quot;")
    .replace(/'/g, "&#039;");
}

function setText(id, text) {
  const el = document.getElementById(id);
  if (el) el.textContent = text;
}

function setValue(id, val) {
  const el = document.getElementById(id);
  if (el) el.value = val;
}

function formatTime() {
  return new Date().toLocaleTimeString("en", { hour: "2-digit", minute: "2-digit" });
}

function getCSSVar(name) {
  return getComputedStyle(document.documentElement).getPropertyValue(name).trim();
}

function copyToClipboard(text) {
  navigator.clipboard?.writeText(text).then(() => {
    showToast("Copied to clipboard ✓");
  }).catch(() => {
    showToast("Could not copy — try manually");
  });
}

function downloadText(filename, text) {
  const a   = document.createElement("a");
  const url = URL.createObjectURL(new Blob([text], { type: "text/plain;charset=utf-8" }));
  a.href     = url;
  a.download = filename;
  a.click();
  URL.revokeObjectURL(url);
}
