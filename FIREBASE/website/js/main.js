// Initialize Firebase
const firebaseConfig = {
  apiKey: "YOUR_API_KEY",
  authDomain: "YOUR_AUTH_DOMAIN",
  databaseURL: "YOUR_DATABASE_URL",
  projectId: "YOUR_PROJECT_ID",
  storageBucket: "YOUR_STORAGE_BUCKET",
  messagingSenderId: "YOUR_MESSAGING_SENDER_ID",
  appId: "YOUR_APP_ID"
};

firebase.initializeApp(firebaseConfig);

// Reference to your Realtime Database
const database = firebase.database();

// Function to display data
function displayData(data) {
  const dataContainer = document.getElementById('data');
  dataContainer.textContent = JSON.stringify(data, null, 2);
}

// Listening to data from a specific path
const dataRef = database.ref('path/to/data');
dataRef.on('value', (snapshot) => {
  const data = snapshot.val();
  displayData(data);
});
