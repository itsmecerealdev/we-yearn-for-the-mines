import { useState } from 'react'
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

  async function generateKeys() {
    setStatus("Generating keys...")
    try {
        setKeys({ privateKey: { name: "42" }, publicKey: { name: "32" } })
        setStatus("Keys generated successfully")
        setReadableKeys(`Private Key: ${keys?.privateKey?.name}, Public Key: ${keys?.publicKey?.name}`)
    } catch (error) {
      setError("Failed to generate keys")
      setStatus("Failed to generate keys")
    }
  }

  return (
    <>
      <main>
        { <p> {status} </p> }
        <button onClick={generateKeys}>Generate Keys</button>
       
            <h2>Prime Number Generation</h2>
            <div class="input-field">
                <textarea id="prime-number-gen" rows="10" cols="50" placeholder="Prime Number Generator Output Here" readonly value={readableKeys}></textarea>
            </div>
            <button>Generate</button>
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
