import "./styles.css";
import { io } from "socket.io-client";
import { useState, useEffect } from "react";

export default function App() {
  const [val1, setVal1] = useState(0);
  const [val2, setVal2] = useState(0);
  const [val3, setVal3] = useState(0);
  const [val4, setVal4] = useState(0);
  const [val5, setVal5] = useState(0);
  const [val6, setVal6] = useState(0);
  const [val7, setVal7] = useState(0);
  const [val8, setVal8] = useState(0);

  useEffect(() => {
    // Connect to the Socket.io server
    const socket = io("http://localhost:3000");

    socket.on("sensor-data", (data) => {
      console.log("Received data from server:", data);
      setVal1(data.val1);
      setVal2(data.val2);
      setVal3(data.val3);
      setVal4(data.val4);
      setVal5(data.val5);
      setVal6(data.val6);
      setVal7(data.val7);
      setVal8(data.val8);
    });

    return () => socket.disconnect();
  }, []);

  return (
    <>
      <div className="app">
        <div className="title">
          <h1>ENIM team</h1>
          <img src="./images/logo-final" alt="" />
        </div>
        <div className="app2">
          <div className="section-box-batterie">
            <h2 className="batterie">Batterie</h2>
            <div>
              <label className="intensite">intensitè</label>
              <label className="tension">tension</label>
              <input
                className="input-intensite"
                type="text"
                value={`      ${val1} A`}
                readOnly
              />
              <input
                className="input-tension"
                type="text"
                value={`      ${val2} V`}
                readOnly
              />
            </div>
            <div>
              <label className="temperature">temperature</label>
            </div>
            <div>
              <input
                className="input-temperature"
                type="text"
                value={`      ${val3} °C`}
                readOnly
              />
            </div>
          </div>

          <div className="section-box-moteur">
            <h2 className="batterie">Moteur</h2>
            <div className="label">
              <label className="vitesse">Vitesse</label>
              <label className="temperature2">Temperature</label>
            </div>
            <input
              className="input-vitesse"
              type="text"
              value={`      ${val4} H/S`}
              readOnly
            />
            <input
              className="input-temperature2"
              type="text"
              value={`      ${val5} °C`}
              readOnly
            />
          </div>
        </div>
        <div className="app3">
          <div className="section-box-horn">
            <h2 className="batterie">Corne</h2>
            <label className="sound">Son</label>
            <input
              className="input-sound"
              type="text"
              value={`      ${val6} Db`}
              readOnly
            />
          </div>
          <div className="section-box-humidite">
            <h2 className="humidite">Humiditè</h2>

            <input
              className="input-humidite"
              type="text"
              value={`      ${val7} %`}
              readOnly
            />
          </div>
        </div>
      </div>
    </>
  );
}
