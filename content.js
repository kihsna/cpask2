chrome.runtime.onMessage.addListener((request) => {
  if (request.action === 'getClipboardText') {
    navigator.clipboard.readText().then(text => {
      chrome.runtime.sendMessage({ action: 'sendToGeminiAPI', text: text });
    }).catch(err => {
      console.error('Failed to read clipboard contents:', err);
    });
  }
});

document.addEventListener('input', function(e) {
  const input = e.target;
  if (!['input', 'textarea'].includes(input.tagName.toLowerCase())) return;

  const value = input.value;

  // Static presets
  if (value.includes('/test')){
    input.value = value.replace('/test', 'The trigger is working');
  }
  if (value.includes('/a1')){
    input.value = value.replace('/a1', 'write c code for the following problem statemnt without comments and use simple and small variable names untill specified in problem.');
  }
  if (value.includes('/a2')) {
    input.value = value.replace('/a2', `write simple java code for the following problem statement using simple and small variable names untill specified in question and use "read" as Scanner object and main programme should be in class Main and dont write comments`);
  }


  // Dynamic presets
  if (value.includes('/cp')) {
    navigator.clipboard.readText().then(text => {
      input.value = value.replace('/cp', text);
    }).catch(err => {
      console.error('Failed to read clipboard contents:', err);
    });
  }

  if (value.includes('/sorry')) {
    chrome.storage.local.get(['geminiResponse'], function(result) {
      input.value = value.replace('/sorry', result.geminiResponse || '[No code block found]');
    });
  }
  if (value.includes('/full')) {
    chrome.storage.local.get(['fullResponse'], function(result) {
      input.value = value.replace('/full', result.fullResponse || '[No response yet]');
    });
  }
});
