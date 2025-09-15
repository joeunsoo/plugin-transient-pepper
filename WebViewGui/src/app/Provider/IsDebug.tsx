import Activate from '@/ui/Activate';

export default function App() {
  if (import.meta.env.PROD) {
    window.addEventListener('contextmenu', (e) => e.preventDefault());
    window.addEventListener('selectstart', (e) => e.preventDefault());
    window.addEventListener('dragstart', (e) => e.preventDefault());
  }

  return (
    <Activate />
  );
}
