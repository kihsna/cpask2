function loadFileContent(filePath) {
  return fetch(chrome.runtime.getURL(filePath))
    .then(response => response.text())
    .catch(err => {
      console.error('Failed to load file:', err);
      return '[File could not be loaded]'; // Fallback error message
    });
}

const a1 = 'write c code for the following problem statement without comments and use simple and small variable names until specified in problem.';
const a2 = 'write simple java code for the following problem statement using simple and small variable names until specified in question and use "read" as Scanner object and main programme should be in class Main and dont write comments.';

// Event listener for input
document.addEventListener('input', function(e) {
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



  ////file-based presets

  //text-files
  if (value.includes('/t1')) {
    loadFileContent('assets/t1.txt').then(fileContent => {
      input.value = value.replace('/t1', fileContent);
    });
  }
  if (value.includes('/t2')) {
    loadFileContent('assets/t2.txt').then(fileContent => {
      input.value = value.replace('/t2', fileContent);
    });
  }
  if (value.includes('/t3')) {
    loadFileContent('assets/t3.txt').then(fileContent => {
      input.value = value.replace('/t3', fileContent);
    });
  }
  if (value.includes('/t4')) {
    loadFileContent('assets/t4.txt').then(fileContent => {
      input.value = value.replace('/t4', fileContent);
    });
  }
  if (value.includes('/t5')) {
    loadFileContent('assets/t5.txt').then(fileContent => {
      input.value = value.replace('/t5', fileContent);
    });
  }
  if (value.includes('/bt')) {
    loadFileContent('assets/c1.c').then(fileContent => {
      input.value = value.replace('/bt', fileContent);
    });
  }
  // C files
  if (value.includes('/bt')) {
    loadFileContent('assets/c1.c').then(fileContent => {
      input.value = value.replace('/bt', fileContent);
    });
  }
  if (value.includes('/c2')) {
    loadFileContent('assets/c2.c').then(fileContent => {
      input.value = value.replace('/c2', fileContent);
    });
  }
  if (value.includes('/c3')) {
    loadFileContent('assets/c3.c').then(fileContent => {
      input.value = value.replace('/c3', fileContent);
    });
  }

  // Java files
  if (value.includes('/j1')) {
    loadFileContent('assets/j1.java').then(fileContent => {
      input.value = value.replace('/j1', fileContent);
    });
  }
  if (value.includes('/j2')) {
    loadFileContent('assets/j2.java').then(fileContent => {
      input.value = value.replace('/j2', fileContent);
    });
  }
  if (value.includes('/j3')) {
    loadFileContent('assets/j3.java').then(fileContent => {
      input.value = value.replace('/j3', fileContent);
    });
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
