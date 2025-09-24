import { useState } from "react";
import reactLogo from "./assets/react.svg";
import viteLogo from "/vite.svg";
import "./App.css";

function App() {
  const [count, setCount] = useState(0);
  const [apiResult, setApiResult] = useState<string | null>(null);

  return (
    <div className="min-h-screen flex flex-col items-center justify-center bg-gray-200">
      <button
        onClick={async () => {
          try {
            const response = await fetch("http://localhost:3000/api/status");
            const data = await response.json();
            setApiResult(`API says: ${data.message}`);
          } catch (error) {
            console.log("Failed to fetch from API");
          }
        }}
        className="mb-8 px-6 py-2 bg-green-600 text-white rounded shadow hover:bg-green-700 transition-colors"
      >
        Call API
      </button>
      {apiResult && (
        <div className="mb-6 px-6 py-3 bg-white rounded shadow text-green-700 font-medium border border-green-300">
          {apiResult}
        </div>
      )}
      <div className="flex space-x-8 mb-8">
        <a href="https://vite.dev" target="_blank" rel="noopener noreferrer">
          <img
            src={viteLogo}
            className="h-16 w-16 transition-transform hover:scale-110"
            alt="Vite logo"
          />
        </a>
        <a href="https://react.dev" target="_blank" rel="noopener noreferrer">
          <img
            src={reactLogo}
            className="h-16 w-16 transition-transform hover:scale-110"
            alt="React logo"
          />
        </a>
      </div>
      <h1 className="text-4xl font-bold mb-6 text-gray-800">Vite + React</h1>
      <div className="bg-white rounded-lg shadow p-8 flex flex-col items-center mb-6">
        <button
          onClick={() => setCount((count) => count + 1)}
          className="px-6 py-2 bg-blue-600 text-white rounded hover:bg-blue-700 transition-colors mb-4"
        >
          count is {count}
        </button>
        <p className="text-gray-600">
          Edit <code className="bg-gray-200 px-1 rounded">src/App.tsx</code> and
          save to test HMR
        </p>
      </div>
      <p className="text-gray-500">
        Click on the Vite and React logos to learn more
      </p>
    </div>
  );
}

export default App;
