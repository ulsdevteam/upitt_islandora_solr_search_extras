<!-- template islandora-objects-subset.tpl.php -->
<?php print $messages; ?>

  <?php if ($tabs): ?>
  <div class="tabs"><?php print render($tabs); ?></div>
  <?php endif; ?>
  <?php if ($action_links): ?>
  <ul class="action-links">
    <?php print render($action_links); ?>
  </ul>
  <?php endif; ?>

  <div id="main-content">
    <div id="metadata-sidebar">
  <?php if ($collection_page_metadata): ?>
  <div class="islandora-basic-collection-metadata">
    <!--<p>using the islandora metadata framework</p>-->
    <?php print $collection_page_metadata; ?> </div>
  <?php endif; ?>
  
	<?php print render($title_prefix); ?>
	<?php if ($collection_img): ?>
  <div class="islandora-basic-collection-metadata-image"> <?php print $collection_img; ?> </div>
  <?php endif; ?>

  <?php
        $block = block_load('islandora_datastream_blocks', 'idb-DESC');
        $renderable_block = _block_get_renderable_array(_block_render_blocks(array($block)));
        print $renderable_block['islandora_datastream_blocks_idb-DESC']['#markup'];
  ?>
  <div class="islandora-basic-collection clearfix">
    <span class="islandora-objects-display-switch">
    <?php
    print theme('links', array(
      'links' => $display_links,
      'attributes' => array('class' => array('links', 'inline')),
      ));
    ?>
  </span>
    <?php print $pager; ?>
    <?php print $content; ?>
    <?php print $pager; ?>
  </div><!-- /end islandora-basic-collection-metadata-desc -->

</div><!-- /end main-content -->


