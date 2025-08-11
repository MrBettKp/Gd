import React, { useState, useEffect } from 'react';
import { ScatterChart, Scatter, XAxis, YAxis, ZAxis, CartesianGrid, Tooltip, Legend } from 'recharts';
import io from 'socket.io-client';

const API_URL = "http://localhost:8000";

function App() {
  const [entities, setEntities] = useState([]);
  const [isConnected, setIsConnected] = useState(false);

  useEffect(() => {
    const socket = io(API_URL);
    
    socket.on("connect", () => {
      setIsConnected(true);
      fetchEntities();
    });

    socket.on("disconnect", () => setIsConnected(false));
    socket.on("entity_update", (data) => setEntities(data.entities));

    return () => socket.disconnect();
  }, []);

  const fetchEntities = async () => {
    const response = await fetch(`${API_URL}/api/entities`);
    const data = await response.json();
    setEntities(data.entities);
  };

  return (
    <div className="dashboard">
      <h1>Game Data Visualization</h1>
      <div className="status">Connection: {isConnected ? "Online" : "Offline"}</div>
      
      <ScatterChart width={800} height={600} margin={{ top: 20, right: 20, bottom: 20, left: 20 }}>
        <CartesianGrid />
        <XAxis type="number" dataKey="x" name="X Position" />
        <YAxis type="number" dataKey="y" name="Y Position" />
        <ZAxis type="number" dataKey="z" range={[0, 1000]} name="Z Position" />
        <Tooltip cursor={{ strokeDasharray: '3 3' }} />
        <Legend />
        <Scatter name="Entities" data={entities} fill="#8884d8" />
      </ScatterChart>
    </div>
  );
}

export default App;
