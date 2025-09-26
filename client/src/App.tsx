import { useState } from "react";
import Button from "@/lib/components/modeButton";
import AnimationButton from "@/lib/components/animationButton";

import "./App.css";

const animations = ["perlin", "sine", "stop"];
const modes = [
  { api: "status", text: "Server Liveness Test" },
  { api: "enableMQTT", text: "Enable MQTT Messages" },
  { api: "disableSteppers", text: "Disable Motors" },
  { api: "home", text: "Home All Diamonds" },
  { api: "resetHome", text: "Reset Home Position" },
];

function App() {
  const [response, setResponse] = useState<ResponseType>({} as ResponseType);

  return (
    <div className="min-h-screen min-w-screen flex items-center justify-center bg-gray-500">
      <div className="grid grid-cols-2 gap-12 w-full max-w-4xl">
        {/* Left Column */}
        <div className="flex flex-col gap-12 bg-gray-200 rounded-lg p-8 shadow">
          {/* Animations Row */}
          <div className="bg-gray-50 rounded-lg p-6 shadow">
            <h2 className="mb-4 text-lg font-semibold">Animations</h2>
            <div className="flex flex-wrap gap-4">
              {animations.map((animation) => (
                <AnimationButton
                  key={animation}
                  api={animation}
                  setResponse={setResponse}
                >
                  {animation.charAt(0).toUpperCase() + animation.slice(1)}
                </AnimationButton>
              ))}
            </div>
          </div>
          {/* Modes Row */}
          <div className="bg-gray-50 rounded-lg p-6 shadow">
            <h2 className="mb-4 text-lg font-semibold">Modes</h2>
            <div className="flex flex-wrap gap-4">
              {modes.map((mode) => (
                <Button key={mode.api} api={mode.api} setResponse={setResponse}>
                  {mode.text}
                </Button>
              ))}
            </div>
          </div>
        </div>
        {/* Right Column */}
        <div className="flex flex-col items-center justify-center h-full bg-gray-100 rounded-lg p-8 shadow">
          <h2 className="mb-4 text-lg font-semibold">Response</h2>
          {response.message && (
            <div
              className={`mb-6 px-6 py-3 bg-white rounded shadow font-medium ${
                response.status === "error"
                  ? "text-red-700 border border-red-300"
                  : "text-green-700 border border-green-300"
              }`}
            >
              {response.message}
            </div>
          )}
        </div>
      </div>
    </div>
  );
}

type ResponseType = {
  status: string;
  message: string;
};

export default App;
