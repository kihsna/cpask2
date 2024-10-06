let lastCopiedText = '';

function extractCode(response) {
  // Extract code block enclosed by ```java or ```c
  const codeRegex = /```(?:java|c)(.*?)```/s;
  const match = response.match(codeRegex);
  return match ? match[1].trim() : '[No code block found]';
}

function sendToGeminiAPI(inputText) {
  const apiKey = 'AIzaSyCQN76GNAUfHFwRk1vQ6fdKJxXZPjirqxg';
  const url = `https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash-latest:generateContent?key=${apiKey}`;

  const data = {
    contents: [{ parts: [{ text: inputText }] }],
    generationConfig: {
      temperature: 1,
      topP: 0.95,
      topK: 40,
      maxOutputTokens: 8192,
      responseMimeType: 'text/plain'
    }
  };

  fetch(url, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(data)
  })
    .then(response => response.json())
    .then(result => {
      if (result?.candidates?.[0]?.content?.parts?.[0]?.text) {
        const fullResponse = result.candidates[0].content.parts[0].text;
        const code = extractCode(fullResponse);

        chrome.storage.local.set({
          geminiResponse: code,
          fullResponse: fullResponse
        }, () => {
          console.log('Gemini API response stored:', code, fullResponse);
        });
      } else {
        console.error('Unexpected response structure from Gemini API', result);
      }
    })
    .catch(error => {
      console.error('Error calling Gemini API:', error);
    });
}

chrome.commands.onCommand.addListener((command) => {
  if (command === 'send-to-gemini') {
    chrome.tabs.query({ active: true, currentWindow: true }, (tabs) => {
      chrome.tabs.sendMessage(tabs[0].id, { action: 'getClipboardText' });
    });
  }
});

chrome.runtime.onMessage.addListener((request) => {
  if (request.action === 'sendToGeminiAPI') {
    sendToGeminiAPI(request.text);
  }
});
