import { useState, useRef, useEffect } from 'react'
import './App.css'

function App() {
	const [status, setStatus] = useState("Connecting to server...")
	const [message, setMessage] = useState("")
	const [error, setError] = useState("")
	const [keys, setKeys] = useState(null)
	const [encodedText, setEncodedText] = useState("")
	const [decodedText, setDecodedText] = useState("")
	const [encryptedText, setEncryptedText] = useState("")
	const [decryptedText, setDecryptedText] = useState("")
	const [readableKeys, setReadableKeys] = useState("")
	const [pubKey, setPubKey] = useState("32")
	const [privKey, setPrivKey] = useState("42")
	const [encoded, setEncoded] = useState("Text To Decode")
	const [decoded, setDecoded] = useState("Text To Encode")
	const [encrypted, setEncrypted] = useState("Text To Decrypt")
	const [decrypted, setDecrypted] = useState("Text To Encrypt")
	
	const [input, setInput] = useState("");
    const socketRef = useRef(null);

	async function generateKeys() {
		setStatus("Generating keys...")
		try {
			setKeys({ privateKey: { name: privKey }, publicKey: { name: pubKey } })
			setStatus("Keys generated successfully")
			setReadableKeys(`Private Key: ${keys?.privateKey?.name},\nPublic Key: ${keys?.publicKey?.name}`)
		} catch (error) {
		  setError("Failed to generate keys")
		  setStatus("Failed to generate keys")
		}
	  }

    useEffect(() => {
		const socket = new WebSocket("ws://www.csci4x.com:6969");
		socketRef.current = socket;

		socket.onopen = () => {
			console.log("Connected to C++ server");
			setStatus("Connected to C++ server");
		};

		socket.onmessage = (event) => {
			console.log("Received:", event.data);

		setMessage(event.data);
	};

       
	socket.onclose = () => {
		console.log("Disconnected from server");
	};

	return () => {
		socket.close();
	};
}, []);

    function sendMessage() {
        if (socketRef.current && socketRef.current.readyState === WebSocket.OPEN) {
			console.log(input);
			socketRef.current.send(input);
            setInput("");
        }
    }

	useEffect(() => {
		if(input != "") {
			setStatus("sent: " + input);
			sendMessage()
		}
	}, [input]);

	useEffect(() => {
		if(message != "") {
			const result = message.split("-");
			switch(result.at(0)) {
				case "1":
					setEncrypted(result.at(1));
					break;
				case "2":
					setDecrypted(result.at(1));
					break;
				case "3":
					setEncoded(result.at(1));
					break;
				case "4":
					setDecoded(result.at(1));
					break;
				default:
					setStatus("Error, malphormed data: " + message);
					break;
			}
		}
	}, [message]);

	function encrypt() {
		const newInput = "1-" + decrypted;
		const status = "Input: " + newInput;

		setInput(newInput);
		setStatus(newInput);
	}

	function decrypt() {
		const newInput = "2-" + encrypted;
		const status = "Input: " + newInput;

		setInput(newInput);
		setStatus(newInput);
	}

	function encode() {
		const newInput = "3-" + decoded;
		const status = "Input: " + newInput;

		setInput(newInput);
		setStatus(newInput);
	}

	function decode() {
		const newInput = "4-" + encoded;
		const status = "Input: " + newInput;

		setInput(newInput);
		setStatus(newInput);
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
        
        <h2>RSA Encryption and Decryption</h2>
        <div class="input-field">
          <textarea id="rsa-encryption" rows="10" cols="50" value={decrypted} onChange={(e) => setDecrypted(e.target.value.replace(/[^0-9\n]/g, ''))}></textarea>
          <textarea id="rsa-decryption" rows="10" cols="50" value={encrypted} onChange={(e) => setEncrypted(e.target.value.replace(/[^0-9\n]/g, ''))}></textarea>
        </div>              
        <div>
          <button onClick={encrypt}>Encrypt</button>
          <button onClick={decrypt}>Decrypt</button>
        </div>  
        <h2>Encoding and Decoding</h2>            
        <div class="input-field">
          <textarea id="encoding" rows="10" cols="50" value={decoded} onChange={(e) => setDecoded(e.target.value)}></textarea>
          <textarea id="decoding" rows="10" cols="50" value={encoded} onChange={(e) => setEncoded(e.target.value.replace(/[^0-9\n]/g, ''))}></textarea>
        </div>
        <div>
          <button onClick={encode}>Encode</button>
          <button onClick={decode}>Decode</button>
        </div>  
      </main>
    </>
  )
}

export default App
