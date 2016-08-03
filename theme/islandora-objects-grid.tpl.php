<?php

/**
 * @file
 * Render a bunch of objects in a list or grid view.
 */
?>
<!-- template islandora-objects-grid.tpl.php -->
<?php print $whamjack_sidebar; ?>

<?php if ($solr_search) : ?>
  <div><?php print $solr_search; ?></div>
<?php endif; ?>






<?php /*
< ?php if (isset($collection_search)) {
  print render($collection_search);
} ? >   
<div class="islandora-objects-grid clearfix">
 < ?php foreach($objects as $object): ?>
   <div class="islandora-objects-grid-item">
     <dl class="islandora-object < ?php print $object['class']; ? >">
       <dt class="islandora-object-thumb">< ?php print $object['thumb']; ? ></dt>
       <dd class="islandora-object-caption">< ?php print $object['link']; ? ></dd>
     </dl>
   </div>
 < ?php endforeach; ? >
</div>
