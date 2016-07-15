<?php

/**
 * @file
 * Render a bunch of objects in a list or grid view.
 */
?>
<?php if (isset($page['sidebar'])) : ?>
  <div><?php print $page['sidebar']; ?></div>
<?php endif; ?>
<?php if ($solr_search) : ?>
  <div><?php print $solr_search; ?></div>
<?php endif; ?>
