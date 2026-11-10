(() => {
  const filterButtons = [...document.querySelectorAll('.filter-button')];
  const projects = [...document.querySelectorAll('.project-row, .build-card')];
  const moreBuilds = document.querySelector('.more-builds');
  const visibleCount = document.getElementById('visible-count');
  const menuToggle = document.querySelector('.menu-toggle');
  const nav = document.getElementById('primary-nav');
  const copyButton = document.querySelector('.copy-email');
  const copyStatus = document.getElementById('copy-status');

  function setFilter(filter) {
    let count = 0;
    projects.forEach((project) => {
      const categories = (project.dataset.category || '').split(' ');
      const show = filter === 'all' || categories.includes(filter);
      project.hidden = !show;
      if (show) count++;
    });
    if (moreBuilds) moreBuilds.hidden = !moreBuilds.querySelector('.build-card:not([hidden])');
    if (visibleCount) visibleCount.textContent = String(count).padStart(2, '0');
    filterButtons.forEach((button) => {
      const active = button.dataset.filter === filter;
      button.classList.toggle('is-active', active);
      button.setAttribute('aria-pressed', String(active));
    });
  }
  filterButtons.forEach((button) => button.addEventListener('click', () => setFilter(button.dataset.filter)));

  if (menuToggle && nav) {
    const close = () => {
      nav.classList.remove('is-open');
      menuToggle.setAttribute('aria-expanded', 'false');
      menuToggle.setAttribute('aria-label', 'Open navigation');
    };
    menuToggle.addEventListener('click', () => {
      const open = menuToggle.getAttribute('aria-expanded') !== 'true';
      menuToggle.setAttribute('aria-expanded', String(open));
      menuToggle.setAttribute('aria-label', open ? 'Close navigation' : 'Open navigation');
      nav.classList.toggle('is-open', open);
    });
    nav.querySelectorAll('a').forEach((link) => link.addEventListener('click', close));
  }

  if (copyButton && copyStatus) {
    copyButton.addEventListener('click', async () => {
      const email = copyButton.dataset.email || '';
      try {
        await navigator.clipboard.writeText(email);
        copyStatus.textContent = 'Email copied.';
      } catch {
        copyStatus.textContent = `Email: ${email}`;
      }
    });
  }

  // Drawing <-> photo. Hover on desktop; tap on touch; Enter/Space where the swap is focusable.
  const touch = window.matchMedia('(hover: none)');
  const toggleSwap = (swap) => {
    const on = swap.classList.toggle('show-photo');
    if (swap.hasAttribute('aria-pressed')) swap.setAttribute('aria-pressed', String(on));
  };
  document.querySelectorAll('.swap').forEach((swap) => {
    swap.addEventListener('click', () => {
      if (touch.matches || !swap.dataset.href) toggleSwap(swap);
      else window.location.href = swap.dataset.href;
    });
    swap.addEventListener('keydown', (e) => {
      if ((e.key === 'Enter' || e.key === ' ') && swap.hasAttribute('tabindex')) { e.preventDefault(); toggleSwap(swap); }
    });
  });

  // Image viewer for documentation figures
  let dialog, stage, view, caption, counter, list = [], index = 0, opener = null;
  const visibleFigures = () => [...document.querySelectorAll('.doc-fig img')].filter((img) => img.offsetParent !== null);
  function buildViewer() {
    dialog = document.createElement('dialog');
    dialog.className = 'lightbox';
    dialog.setAttribute('aria-label', 'Image viewer');
    dialog.innerHTML = '<div class="lb-bar"><span class="lb-count" aria-live="polite"></span><span class="lb-tip">Click image to zoom · Esc to close</span>'
      + '<div class="lb-actions"><button type="button" class="lb-prev" aria-label="Previous image">←</button>'
      + '<button type="button" class="lb-next" aria-label="Next image">→</button>'
      + '<button type="button" class="lb-close" aria-label="Close image viewer">✕</button></div></div>'
      + '<div class="lb-stage"><img alt="" /></div><p class="lb-cap"></p>';
    document.body.appendChild(dialog);
    stage = dialog.querySelector('.lb-stage'); view = dialog.querySelector('.lb-stage img');
    caption = dialog.querySelector('.lb-cap'); counter = dialog.querySelector('.lb-count');
    dialog.querySelector('.lb-close').addEventListener('click', () => dialog.close());
    dialog.querySelector('.lb-prev').addEventListener('click', () => step(-1));
    dialog.querySelector('.lb-next').addEventListener('click', () => step(1));
    view.addEventListener('click', () => stage.classList.toggle('zoomed'));
    stage.addEventListener('click', (e) => { if (e.target === stage) dialog.close(); });
    dialog.addEventListener('keydown', (e) => {
      if (e.key === 'ArrowRight') step(1);
      if (e.key === 'ArrowLeft') step(-1);
    });
    dialog.addEventListener('close', () => {
      document.documentElement.classList.remove('lb-open');
      if (opener) opener.focus();
    });
  }
  function show() {
    const img = list[index];
    view.src = img.currentSrc || img.src;
    view.alt = img.alt;
    const cap = img.closest('figure') && img.closest('figure').querySelector('figcaption');
    caption.textContent = cap ? cap.textContent : '';
    counter.textContent = `${index + 1} / ${list.length}`;
    stage.classList.remove('zoomed');
    dialog.querySelector('.lb-prev').disabled = list.length < 2;
    dialog.querySelector('.lb-next').disabled = list.length < 2;
  }
  function step(d) { index = (index + d + list.length) % list.length; show(); }
  function openViewer(img) {
    if (!dialog) buildViewer();
    list = visibleFigures(); index = Math.max(0, list.indexOf(img)); opener = img;
    show();
    dialog.showModal();
    document.documentElement.classList.add('lb-open');
    dialog.querySelector('.lb-close').focus();
  }
  document.querySelectorAll('.doc-fig img').forEach((img) => {
    img.tabIndex = 0;
    img.setAttribute('aria-label', `${img.alt}. Open larger view.`);
  });
  document.addEventListener('click', (e) => {
    const img = e.target.closest && e.target.closest('.doc-fig img');
    if (img) { e.preventDefault(); openViewer(img); }
  });
  document.addEventListener('keydown', (e) => {
    const img = e.target.closest && e.target.closest('.doc-fig img');
    if (img && (e.key === 'Enter' || e.key === ' ')) { e.preventDefault(); openViewer(img); }
  });

  // Highlight the current section in the project index
  if ('IntersectionObserver' in window) {
    document.querySelectorAll('.doc-toc').forEach((toc) => {
      const links = [...toc.querySelectorAll('a[data-sec]')];
      const heads = links.map((a) => document.getElementById(a.dataset.sec)).filter(Boolean);
      const io = new IntersectionObserver((entries) => {
        entries.forEach((en) => {
          if (!en.isIntersecting) return;
          links.forEach((a) => a.classList.toggle('is-current', a.dataset.sec === en.target.id));
        });
      }, { rootMargin: '-20% 0px -70% 0px' });
      heads.forEach((h) => io.observe(h));
    });
  }

  // Skill stars: the data-level attribute (0–5, halves allowed) drives the fill and the label
  document.querySelectorAll('.stars[data-level]').forEach((el) => {
    const level = Math.max(0, Math.min(5, parseFloat(el.dataset.level) || 0));
    el.style.setProperty('--level', level);
    el.setAttribute('aria-label', level ? `Skill level ${level} out of 5` : 'Skill level not rated yet');
  });

  const year = document.getElementById('year');
  if (year) year.textContent = new Date().getFullYear();
})();
