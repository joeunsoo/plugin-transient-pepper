import Activate from '@/ui/Activate';

export default function App() {
  if (import.meta.env.PROD) {
    window.addEventListener('contextmenu', (e) => e.preventDefault());
  }

  return <Activate />;
}
