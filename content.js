chrome.runtime.onMessage.addListener((request) => {
  if (request.action === 'getClipboardText') {
    navigator.clipboard.readText().then(text => {
      chrome.runtime.sendMessage({ action: 'sendToGeminiAPI', text: text });
    }).catch(err => {
      console.error('Failed to read clipboard contents:', err);
    });
  }
});

function loadFileContent(filePath) {
  return fetch(chrome.runtime.getURL(filePath))
    .then(response => response.text())
    .catch(err => {
      console.error('Failed to load file:', err);
      return '[File could not be loaded]';
    });
}

const a1 = 'write c code for the following problem statement without comments and use simple and small variable names until specified in problem.';
const a2 = 'write simple java code for the following problem statement using simple and small variable names until specified in question and use "read" as Scanner object and main programme should be in class Main and dont write comments.';
document.addEventListener('input', async function (e) {
  const input = e.target;
  if (!['input', 'textarea'].includes(input.tagName.toLowerCase())) return;
  const value = input.value;

  // Static presets
  if (value.includes('/test')) {
    input.value = value.replace('/test', 'The trigger is working');
  }
  if (value.includes('/dont')) {
    input.value = value.replace('/dont', 'dont write comments and input prompts');
  }
  if (value.includes('/a1')) {
    input.value = value.replace('/a1', a1);
  }
  if (value.includes('/a2')) {
    input.value = value.replace('/a2', a2);
  }

  // File-based presets
  const filePresets = [
    { trigger: '/t1', filePath: 'assets/t1.txt' },
    { trigger: '/t2', filePath: 'assets/t2.txt' },
    { trigger: '/t3', filePath: 'assets/t3.txt' },
    { trigger: '/t4', filePath: 'assets/t4.txt' },
    { trigger: '/t5', filePath: 'assets/t5.txt' },
    { trigger: '/bt', filePath: 'assets/c1.c' },  // C files
    { trigger: '/c2', filePath: 'assets/c2.c' },
    { trigger: '/c3', filePath: 'assets/c3.c' },
    { trigger: '/j1', filePath: 'assets/j1.java' },  // Java files
    { trigger: '/j2', filePath: 'assets/j2.java' },
    { trigger: '/j3', filePath: 'assets/j3.java' },
  ];

  for (const preset of filePresets) {
    if (value.includes(preset.trigger)) {
      const fileContent = await loadFileContent(preset.filePath);
      input.value = value.replace(preset.trigger, fileContent);
      return; // Exit after replacing to avoid unnecessary checks
    }
  }

  // Dynamic presets
  if (value.includes('/cp')) {
    try {
      const clipboardText = await navigator.clipboard.readText();
      input.value = value.replace('/cp', clipboardText);
    } catch (err) {
      console.error('Failed to read clipboard contents:', err);
    }
  }

  if (value.includes('/sorry')) {
    chrome.storage.local.get(['geminiResponse'], function (result) {
      input.value = value.replace('/sorry', result.geminiResponse || '[No code block found]');
    });
  }

  if (value.includes('/full')) {
    chrome.storage.local.get(['fullResponse'], function (result) {
      input.value = value.replace('/full', result.fullResponse || '[No response yet]');
    });
  }
});
