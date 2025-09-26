import React from "react";

const ModeButton: React.FC<ButtonProps> = ({ children, api, setResponse }) => {
  const onClick = async () => {
    try {
      const response = await fetch(`http://localhost:3000/api/${api}`, {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ test: 1 }),
      });

      const { message, status } = await response.json();

      setResponse({ status, message });
      console.log(message);
    } catch (error) {
      setResponse({ status: "error", message: "Failed to fetch" });
      console.log("Failed to fetch", error);
    }
  };

  return (
    <button
      onClick={onClick}
      className="mb-8 px-6 py-2 bg-purple-600 text-white rounded shadow hover:bg-purple-700 transition-colors touch-auto cursor-pointer"
    >
      {children}
    </button>
  );
};

export default ModeButton;

type ButtonProps = {
  children: React.ReactNode;
  onClick?: () => void;
  api: string;
  setResponse: React.Dispatch<
    React.SetStateAction<{ status: string; message: string }>
  >;
};
