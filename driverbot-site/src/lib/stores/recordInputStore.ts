import { writable } from "svelte/store";

// Define the initial state of the store
const initialState: { key: string; time: Date }[] = [];
let isRecording = false;

// Create the store
const recordInputStore = writable(initialState);

// Function to add a new record to the store
const addRecord = (key: string) => {
  if (!isRecording) return;
  const record = { key, time: new Date() };
  recordInputStore.update((state) => [...state, record]);
};

const setIsRecording = (value: boolean) => {
  isRecording = value;
};

export { recordInputStore, addRecord, setIsRecording };
