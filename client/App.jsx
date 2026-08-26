import { useState, useRef, useEffect } from 'react'
import './App.css'

function App() {
  const [status, setStatus] = useState("Connecting to server...")
  const [message, setMessage] = useState([])
  const [error, setError] = useState("")
  const [keys, setKeys] = useState(null)
  const [primeOutput, setPrimeOutput] = useState("")
  const [plainText, setPlainText] = useState("")
  const [encodedText, setEncodedText] = useState("")
  const [decodedText, setDecodedText] = useState("")
  const [encryptedText, setEncryptedText] = useState("")
  const [decryptedText, setDecryptedText] = useState("")
  const [readableKeys, setReadableKeys] = useState("")
  const [pubKeyDummy, setPubKeyDummy] = useState("32")
  const [privKeyDummy, setPrivKeyDummy] = useState("42")

  async function generateKeys() {
    setStatus("Generating keys...")
    try {
        setKeys({ privateKey: { name: privKeyDummy }, publicKey: { name: pubKeyDummy } })
        setStatus("Keys generated successfully")
        setReadableKeys(`Private Key: ${keys?.privateKey?.name}, Public Key: ${keys?.publicKey?.name}`)
    } catch (error) {
      setError("Failed to generate keys")
      setStatus("Failed to generate keys")
    }
  }

  const [messages, setMessages] = useState([]);

    const [input, setInput] = useState("");

    const socketRef = useRef(null);

    useEffect(() => {

        const socket = new WebSocket("ws://localhost:8080");

        // Save the socket so other functions can use it
        socketRef.current = socket;

        socket.onopen = () => {
            console.log("Connected to C++ server");
        };

        //whenevr u get a msg this runs
        socket.onmessage = (event) => {
            console.log("Received:", event.data);

            setMessages((oldMessages) => [
                ...oldMessages,
                event.data
            ]);
        };

       
        socket.onclose = () => {
            console.log("Disconnected from server");
        };

        // closes the scket when the connection stops
        return () => {
            socket.close();
        };
    }, []);

    function sendMessage() {
        if (
            socketRef.current &&
            socketRef.current.readyState === WebSocket.OPEN
        ) {
            socketRef.current.send(input);

            setInput("");
        }
    }

  return (
    <>
      <main>
        <br></br>
        { <p> {status} </p> }
        <br></br>
        <h2>Key Generation</h2>
        <button onClick={generateKeys}>Generate Keys</button>
        <textarea id="" rows="10" cols="50" placeholder="Prime Number Generator Output Here" readonly value={readableKeys}></textarea>
        
            {/* <h2>Prime Number Generation</h2>
            <div class="input-field">
                <textarea id="prime-number-gen" rows="10" cols="50" placeholder="Prime Number Generator Output Here" readonly value={readableKeys}></textarea>
            </div>
            <button>Generate</button> */}
        <h2>RSA Encryption and Decryption</h2>
        <div class="input-field">
          <textarea id="rsa-encryption" rows="10" cols="50" placeholder="Text to Encrypt"></textarea>
          <textarea id="rsa-decryption" rows="10" cols="50" placeholder="Text to Decrypt"></textarea>
        </div>              
        <div>
          <button>Encrypt</button>
          <button>Decrypt</button>
        </div>  
        <h2>Encoding and Decoding</h2>            
        <div class="input-field">
          <textarea id="encoding" rows="10" cols="50" placeholder="Text to Encode"></textarea>
          <textarea id="decoding" rows="10" cols="50" placeholder="Text to Decode"></textarea>
        </div>
        <div>
          <button>Encode</button>
          <button>Decode</button>
        </div>  
      </main>
    </>
  )
}

export default App
